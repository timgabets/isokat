project('isocat', 'c',
	version: '0.1.2',
	default_options: [
		'c_std=c11',
		'werror=true',
	])

src = [
  'src/zf_log.c',
  'src/http_parser.c',
  'src/main.c'
]

incdir = include_directories('include')

executable('isocat', src, include_directories : incdir)
