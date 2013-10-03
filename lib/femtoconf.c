/*
 * Copyright (C) 2013  Jan Dvorak <mordae@anilinux.org>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "femtoconf.h"

struct option {
	char name[64];
	char value[128];
	struct option *next;
};

struct conf {
	struct option *options;
};

inline static char *rtrim(char *str)
{
	ssize_t i, len = strlen(str);

	for (i = len - 1; i >= 0; i--)
		if (isspace(str[i]))
			str[i] = '\0';
		else
			break;

	return str;
}

static struct option *load_option(FILE *fp)
{
	struct option *option;
	char eol[2] = "";
	int m;

	option = calloc(1, sizeof(*option));

start:
	m = fscanf(fp, " %63s %127[^\n] %1[\n]",
		       option->name, option->value, eol);

	rtrim(option->value);

	if (-1 == m) {
		free(option);
		return NULL;
	}

	if (0 == m || '#' == option->name[0])
		goto start;

	return option;
}

struct conf *conf_load(const char *path)
{
	struct option *option, *stack = NULL;
	struct conf *conf;
	FILE *fp;

	if (NULL == (fp = fopen(path, "r")))
		return NULL;

	while (NULL != (option = load_option(fp))) {
		option->next = stack;
		stack = option;
	}

	fclose(fp);

	conf = calloc(1, sizeof(*conf));

	while (stack) {
		option = stack;
		stack = option->next;
		option->next = conf->options;
		conf->options = option;
	}

	return conf;
}

static void free_options(struct option *option)
{
	struct option *next;

	while (option) {
		next = option->next;
		free(option);
		option = next;
	}
}

void conf_free(struct conf *conf)
{
	if (NULL == conf)
		return;

	free_options(conf->options);
	free(conf);
}

const char *conf_get(const struct conf *conf,
                     const char *name, size_t n, const char *dfl)
{
	size_t seen = 0;
	struct option *iter;

	for (iter = conf->options; iter; iter = iter->next)
		if (0 == strcmp(name, iter->name)) {
			if (seen++ == n)
				return iter->value;
		}

	return dfl;
}
