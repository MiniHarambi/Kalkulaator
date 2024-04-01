kalkulaator_sources = [
  'main.c',
  'kalkulaator-window.c',
  'kalkulaator-application.c',
  'kalkulaator-calc.c',
  'kalkulaator-application.h',
  'kalkulaator-window.h',
  'kalkulaator-calc.h',
  'programming-window.c',
  'programming-window.h',
]

kalkulaator_deps = [
  dependency('gtk4', 'lm'),
]

gnome = import('gnome')

kalkulaator_sources += gnome.compile_resources('kalkulaator-resources',
  'kalkulaator.gresource.xml',
  c_name: 'kalkulaator'
)

executable('kalkulaator', kalkulaator_sources,
  dependencies: kalkulaator_deps,
  install: true,
  link_args: ['-lgtk-4', '-lm'],
)
