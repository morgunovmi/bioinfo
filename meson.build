project('bioinfo', 'cpp',
        default_options: ['default_library=static', 'cpp_std=c++2a']
        )

fmt = dependency('fmt')
rangev3 = dependency('range-v3')

incdir = include_directories('src')

sources = files([
  'src/utils/util.cpp',
  'src/p1/pattern_count.cpp',
  'src/p2/find_clums.cpp',
  'src/p3/minimum_skew.cpp',
  'src/p4/approx_occurences.cpp',
  'src/p5/frequent_words.cpp',
  'src/main.cpp',
  ])

executable('app', sources, include_directories : incdir,
          dependencies : [fmt, rangev3])
