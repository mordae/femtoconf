/*
 * Copyright (C) 2011  Jan Dvorak <mordae@anilinux.org>
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

#include "femtoconf.h"
#include "cutest.h"

inline static int eq(const char *a, const char *b)
{
	return 0 == strcmp(a, b);
}

decl_test(load_free)
{
	struct conf *conf = conf_load("lib/test/test.conf");
	assert(NULL != conf);
	conf_free(conf);
}

decl_test(single)
{
	struct conf *conf = conf_load("lib/test/test.conf");

	assert(NULL != conf);
	assert(eq("bar", conf_get(conf, "foo", 0, "fail")));
	assert(NULL == conf_get(conf, "foo", 1, NULL));

	assert(eq("kitty kitty", conf_get(conf, "hello", 0, "fail")));
	assert(NULL == conf_get(conf, "hello", 1, NULL));

	conf_free(conf);
}

decl_test(empty)
{
	struct conf *conf = conf_load("lib/test/test.conf");

	assert(NULL != conf);
	assert(eq("", conf_get(conf, "end", 0, "fail")));

	conf_free(conf);
}

decl_test(multi)
{
	struct conf *conf = conf_load("lib/test/test.conf");

	assert(NULL != conf);
	assert(eq("42", conf_get(conf, "baz", 0, "fail")));
	assert(eq("13", conf_get(conf, "baz", 1, "fail")));
	assert(eq("007", conf_get(conf, "baz", 2, "fail")));
	assert(NULL == conf_get(conf, "baz", 3, NULL));

	conf_free(conf);
}
