/*
 * shell_fs.c
 *
 *  Created on: Jan 15, 2024
 *      Author: andrew
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#include "main.h"
#include "shell.h"
#include "fs.h"

/** */
void shell_fsinfo_command(const char *command_string)
{
	printf("Number of flash blocks: %ld\n", lfs_cfg.block_count);
	printf("Erase flash block size: %ld bytes\n", lfs_cfg.block_size);
	printf("Flash prog size: %ld bytes\n", lfs_cfg.prog_size);
	printf("--\n");
	uint32_t used = lfs_fs_size(&lfs) * lfs_cfg.block_size;
	uint32_t total = lfs_cfg.block_count * lfs_cfg.block_size;
	printf("total bytes = %ld, used bytes = %ld free bytes = %ld\n", total, used, total - used);
}

/** */
void shell_fstest_command(const char *command_string)
{
	lfs_file_t file;
	uint32_t test_count = 0;

	lfs_file_open(&lfs, &file, "test", LFS_O_RDWR | LFS_O_CREAT);
	lfs_file_read(&lfs, &file, &test_count, sizeof(test_count));

	printf("test file contents %ld\n", test_count);
	test_count += 1;
	lfs_file_rewind(&lfs, &file);
	lfs_file_write(&lfs, &file, &test_count, sizeof(test_count));
	lfs_file_close(&lfs, &file);
	printf("test file contents incremented by 1\n");
}

/** */
void shell_format_command(const char *command_string)
{
	printf("are you sure (y/n)\n");

	char ch = getchar();

	if (ch == 'y')
	{
		printf("\nreformatting\n");

		if (lfs_format(&lfs, &lfs_cfg) == 0)
		{
			printf("formatting complete\n");

			int err = lfs_mount(&lfs, &lfs_cfg);

			if (err < 0)
			{
				printf("could not mount filesystem\n");
			}
		}
		else
		{
			printf("formatting failed\n");
		}
	}
}

/** */
void shell_ls_command(const char *command_string)
{
	uint8_t arg1_len;
	const char *arg1 = shell_get_parameter(command_string, 1, &arg1_len);

	lfs_dir_t dir;
	struct lfs_info info;

	char path[LFS_NAME_MAX];
	memset(path, 0, LFS_NAME_MAX);

	if (arg1 != NULL)
	{
		strcpy(path, arg1);
	}

	lfs_dir_open(&lfs, &dir, path);

	while (lfs_dir_read(&lfs, &dir, &info) > 0)
	{
		printf("%s\t%ld\n", info.name, info.size);
	}

	lfs_dir_close(&lfs, &dir);
}

/** */
static void list_dir(char *path, int level)
{
	lfs_dir_t dir;
	struct lfs_info info;

	if (lfs_dir_open(&lfs, &dir, path) < 0)
	{
		printf("could not open directory %s\n", path);
		return;
	}

	while (lfs_dir_read(&lfs, &dir, &info) > 0)
	{
		if ((strcmp(info.name, ".") == 0) || (strcmp(info.name, "..") == 0))
		{
			continue;
		}

		for (int i = 0; i < level; i++)
		{
			printf("    ");
		}

		if (info.type == LFS_TYPE_DIR)
		{
			printf("\x1B[94m%s\x1B[97m\n", info.name); // print in blue
			strcat(path, "/");
			strcat(path, info.name);
			list_dir(path, ++level);
			break;
		}
		else
		{
			printf("%s\n", info.name);
		}
	}

	if (lfs_dir_close(&lfs, &dir) < 0)
	{
		printf("could not close directory %s\n", path);
	}
}

/** */
void shell_tree_command(const char *command_string)
{
	uint8_t arg1_len;
	const char *arg1 = shell_get_parameter(command_string, 1, &arg1_len);

	char path[LFS_NAME_MAX];
	memset(path, 0, LFS_NAME_MAX);

	if (arg1 != NULL)
	{
		strcpy(path, arg1);
	}

	list_dir(path, 0);
}

/** */
void shell_rm_command(const char *command_string)
{
	uint8_t arg1_len;
	const char *arg1 = shell_get_parameter(command_string, 1, &arg1_len);

	if (arg1 != NULL)
	{
		struct lfs_info info;

		if(lfs_stat(&lfs, arg1, &info) < 0)
		{
			printf("could not stat file %s\n", arg1);
			return;
		}

		if(info.type == LFS_TYPE_DIR)
		{
			printf("%s is a directory\n", arg1);
			return;
		}
		if (lfs_remove(&lfs, arg1) < 0)
		{
			printf("error removing file %s\n", arg1);
		}
	}
	else
	{
		printf("no file name specified\n");
	}

}

/** */
void shell_cp_command(const char *command_string)
{
	uint8_t arg1_len;
	uint8_t arg2_len;
	const char *arg1 = shell_get_parameter(command_string, 1, &arg1_len);
	const char *arg2 = shell_get_parameter(command_string, 2, &arg2_len);
	lfs_file_t src_file;
	lfs_file_t dst_file;
	char src_filename[64];
	char dst_filename[64];

	if (!arg1)
	{
		printf("no source file specified\n");
		return;
	}

	if (!arg2)
	{
		printf("no destination file specified\n");
		return;
	}

	memset(src_filename, 0, sizeof(src_filename));
	memset(dst_filename, 0, sizeof(dst_filename));
	strncpy(src_filename, arg1, arg1_len);
	strncpy(dst_filename, arg2, arg2_len);

	if (lfs_file_open(&lfs, &src_file, src_filename, LFS_O_RDONLY) < 0)
	{
		printf("could not open source file\n");
		return;
	}

	if (lfs_file_open(&lfs, &dst_file, dst_filename, LFS_O_WRONLY |LFS_O_CREAT | LFS_O_TRUNC) < 0)
	{
		printf("could not open destination file\n");
		lfs_file_close(&lfs, &src_file);
		return;
	}

	uint8_t buffer[256];

	while (true)
	{
		uint32_t read = lfs_file_read(&lfs, &src_file, buffer, sizeof(buffer));

		if (read == 0)
		{
			break;
		}
		if (read < 0)
		{
			printf("error reading source file\n");
			break;
		}

		uint32_t written = lfs_file_write(&lfs, &dst_file, &buffer, read);

		if (read != written || written < 0)
		{
			printf("error writing destination file\n");
			break;
		}
	}

	lfs_file_close(&lfs, &src_file);
	lfs_file_close(&lfs, &dst_file);

	return;
}

/** */
void shell_mv_command(const char *command_string)
{
	uint8_t arg1_len;
	uint8_t arg2_len;
	const char *arg1 = shell_get_parameter(command_string, 1, &arg1_len);
	const char *arg2 = shell_get_parameter(command_string, 2, &arg2_len);

	char src_filename[16];
	char dst_filename[16];

	if (!arg1)
	{
		printf("no source file specified\n");
		return;
	}

	if (!arg2)
	{
		printf("no destination file specified\n");
		return;
	}

	if(lfs_rename(&lfs, src_filename, dst_filename) < 0)
	{
		printf("could not move source file %s to destination %s\n", src_filename, dst_filename);
	}
}

/** */
void shell_mkdir_command(const char *command_string)
{
	uint8_t arg1_len;
	const char *arg1 = shell_get_parameter(command_string, 1, &arg1_len);

	if (arg1 != NULL)
	{
		if (lfs_mkdir(&lfs, arg1) < 0)
		{
			printf("error creating directory %s\n", arg1);
		}
	}
	else
	{
		printf("no directory name specified\n");
	}
}

/** */
void shell_rmdir_command(const char *command_string)
{
	uint8_t arg1_len;
	const char *arg1 = shell_get_parameter(command_string, 1, &arg1_len);

	if (arg1 != NULL)
	{
		if (lfs_remove(&lfs, arg1) < 0)
		{
			printf("error removing directory %s (not empty?)\n", arg1);
		}
	}
	else
	{
		printf("no directory name specified\n");
	}
}

/** */
void shell_cat_command(const char *command_string)
{
	uint8_t arg1_len;
	uint8_t arg2_len;
	const char *arg1 = shell_get_parameter(command_string, 1, &arg1_len);
	const char *arg2 = shell_get_parameter(command_string, 2, &arg2_len);
	lfs_file_t file;

	if (arg1 != NULL)
	{
		char filename[32];
		memset(filename, 0, 32);
		strncpy(filename, arg1, arg1_len);
		int err = lfs_file_open(&lfs, &file, filename, LFS_O_RDWR);

		if (err < 0)
		{
			printf("could not open file\n");
			return;
		}

		while (true)
		{
			unsigned char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			int read = lfs_file_read(&lfs, &file, buffer, sizeof(buffer));

			if (read <= 0)
			{
				break;
			}

			if (shell_arg_is("binary", arg2, arg2_len))
			{
				shell_print_array(0, buffer, read);
			}
			else
			{
				printf("%.*s", read, buffer);
			}
		}

		lfs_file_close(&lfs, &file);
	}
	else
	{
		printf("no file name specified\n");
	}
}

