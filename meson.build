project('isokat', 'c',
	version: '0.1.3',
	default_options: [
		'c_std=c11',
		'werror=true',
	])

default_args = ['-D_POSIX_C_SOURCE=200112L', '-D_XOPEN_SOURCE=500', '-Wwrite-strings']
dep_criterion = dependency('criterion')

src = [
  'src/formats/common.c',
  'src/zf_log.c',
  'src/http_parser.c',
  'src/cJSON.c',
]

incdir = include_directories('include')

executable('isokat',
	src, 'src/main.c',
	include_directories : incdir,
	c_args: default_args)

src_tests = [
	'tests/formats/test_common.c',
]

test('iddqd', executable('tests',
	src, src_tests,
	dependencies: dep_criterion,
	include_directories : incdir,
	c_args: default_args))