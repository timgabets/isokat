project('isokat', 'c',
	version: '0.1.3',
	default_options: [
		'c_std=c11',
		'werror=true',
	])

src = [
  'src/formats/common.c',
  'src/zf_log.c',
  'src/http_parser.c',
  'src/cJSON.c',
  'src/main.c'
]

incdir = include_directories('include')

executable('isokat',
	src,
	include_directories : incdir,
	c_args: ['-D_POSIX_C_SOURCE=200112L', '-Wwrite-strings'],)
