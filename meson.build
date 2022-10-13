project('bioinfo', 'cpp',
        default_options: ['default_library=static', 'cpp_std=c++2a']
        )

fmt = dependency('fmt')

incdir = include_directories('src')

sources = files([
  'src/utils/util.cpp',
  'src/p1/pattern_count.cpp',
  'src/p2/find_clums.cpp',
  'src/p3/minimum_skew.cpp',
  'src/p4/approx_occurences.cpp',
  'src/p5/frequent_words.cpp',
  'src/p6/profile_most_probable.cpp',
  'src/p7/greedy_motif_search.cpp',
  'src/p8/randomized_motif_search.cpp',
  'src/p9/gibbs_sampler.cpp',
  'src/p10/distance_between_pattern_and_strings.cpp',
  'src/p11/find_eulerian_path.cpp',
  'src/p12/k_universal_string.cpp',
  'src/p14/contigs_from_reads.cpp',
  'src/main.cpp',
  ])

executable('app', sources, include_directories : incdir,
          dependencies : [fmt])
