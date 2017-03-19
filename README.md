# Activity 3: Backdoor

## List
- ./interpreter/
    - interpreter.c: bytecode를 한 줄씩 읽어서 각 opcode의 함수를 처리해주는 인터프리터.
    - minivm.h: minivm.c의 header file.
    - minivm.c: pc를 이용해서 명령을 차례대로 읽어주고 맞는 함수를 호출하는 기능.

- ./login/login.mini: 'User: user', 'Password: password'를 입력하면 'Success'를 출력하고 그 외의 경우 'Failure'를 출력하는 mini language file.

- ./test/test.mini: 소문자와 대문자를 서로 바꿔주는 기능을 하는 mini language file.

- ./test/test.md: test.mini에 대한 설명.

- ./backdoor/
    * interpreter.c: ./interpreter/interpreter.c의 동작을 하는 인터프리터에서 'User: superuser'를 입력하면 바로 'Success'를 출력하게 하도록 하는 backdoor 기능을 구현한 인터프리터.
    * minivm.h: minivm.c의 header file.
    * minivm.c: pc를 이용해서 명령을 차례대로 읽어주고 맞는 함수를 호출하는 기능.

- ./compiler/comiler.ml: mini language를 bytecode로 컴파일해주는 기능. 과제에서 주어진 컴파일러를 수정하지 않고 사용하였다.


## What I learned
- Interpreter의 기본적인 동작 과정을 알게 되었다.
- Interpreter의 몇몇 기능을 구현하면서 내부에서 어떤 식으로 돌아가는지 알게 되었다.
- Backdoor가 무엇인지 알게 되었으며 어떤 식으로 돌아가는지 알게 되었다.
- Mini Language Code를 만들면서 Assembly Code에 대한 기본을 알게 되었다.

