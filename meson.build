project('convoy', 'c')

required_args = ['-std=c99', '-pedantic', '-Wall', '-Wextra', '-g']
add_project_arguments(required_args, language : 'c')

test('test-circbuf', executable('test-circbuf', 'test/test-circbuf.c'))
test('test-deque', executable('test-deque', 'test/test-deque.c'))
test('test-queue', executable('test-queue', 'test/test-queue.c'))
test('test-splat', executable('test-splat', 'test/test-splat.c'))
test('test-stack', executable('test-stack', 'test/test-stack.c'))
