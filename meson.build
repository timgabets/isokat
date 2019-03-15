project('isocat', 'c',
	version: '0.1.1',
	default_options: [
		'c_std=c11'
	])

src = [
  'src/zf_log.c',
  'src/main.c'
]

incdir = include_directories('include')

executable('isocat', src, include_directories : incdir)
