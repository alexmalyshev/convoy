project(
  'convoy',
  'c',
  default_options : [
    'buildtype=debug',
    'c_std=c99',
    'debug=true',
    'warning_level=3',
    'werror=true',
  ]
)

inc = include_directories('include')

tests = [
  'circbuf',
  'deque',
  'queue',
  'splat',
  'stack',
]

foreach item : tests
  name = 'test-' + item
  binary = executable(name, 'test/' + name + '.c', include_directories : inc)
  test(name, binary)
endforeach
