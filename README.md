# 자막 관리 프로그램 구현 (Data Structure Project 1)

2024학년도 데이터구조 과제 1 – Queue, Binary Search Tree, Linked List를 활용한 자막 관리 프로그램

---

## Authors

장현웅 · 2021202087

---

## 프로젝트 개요

이 프로젝트의 목표는 **Queue**, **Binary Search Tree**, **Linked List**와 같은 기본 자료구조를 이용하여 자막을 관리하는 프로그램을 만드는 것이다. 입력 파일인 `command.txt`에는 실행할 명령어들이 한 줄씩 저장되어 있고, `subtitle.txt`에는 정렬되지 않은 시간과 자막 내용이 저장되어 있다. 프로그램은 명령어를 읽어 자막을 큐에 적재한 후 이진 검색 트리로 옮기고, 특정 시간 범위를 추출해 링크드 리스트 형태의 섹션으로 저장하는 등 다양한 연산을 수행한다. 모든 명령의 수행 결과는 `log.txt`에 기록된다.

프로젝트를 통해 다양한 자료구조의 사용 방법을 익히고, 각 자료구조의 동작을 처리하는 데 필요한 알고리즘을 이해하는 것이 목적이다. 또한 `Time` 클래스를 정의하여 `XX:XX:XX` 형태의 시간을 표현하고 비교 연산자 및 입출력 연산자를 오버로딩하여 프로젝트 전반에 걸쳐 시간 값 비교를 효율적으로 수행하였다.

---

## 프로그램 구성 요약

본 구현은 다음과 같이 클래스를 설계하고 서로 연동하여 자막을 관리한다:

* **`Time` 클래스** – 시간(`시:분:초`)을 `short` 단위로 저장하고 `<`, `>`, `==` 등의 비교 연산자를 오버로딩한다. 입력과 출력 연산자도 오버로딩하여 문자열로부터 안전하게 시간을 읽어온다.

* **`SubtitleQueue` 클래스** – `subtitle.txt`에서 읽어들인 데이터(`Datapair = pair<Time, string>`)를 저장하는 큐 구조이다. `Push`와 `Pop` 기본 연산을 지원하며, `Front`와 `PrintQueue` 연산을 통해 큐의 맨 앞/전체 데이터를 확인할 수 있다. 중간 삽입이 없는 기본 큐이므로 링크드 리스트 노드(`SubtitleQueueNode`)만 포함한다.

* **`SubtitleBST` 클래스** – 큐에서 꺼낸 자막을 시간 값을 key로 하여 저장하는 이진 검색 트리이다. `Insert`로 노드를 삽입하고 `PrintBST`로 중위 순회를 수행하여 모든 자막을 시간순으로 출력한다. `SearchRange`는 `[start_time, end_time]` 범위에 있는 노드를 찾아 임시 버퍼 큐로 반환하고, `DeleteEveryEqual`과 `DeleteUnder`는 주어진 시간과 동일한/이하의 노드를 삭제한다.

* **`SectionList` 클래스** – SECTION 명령으로 생성되는 섹션 헤더들을 관리하는 링크드 리스트 구조이다. `GenerateNewSection`으로 섹션 헤더를 리스트 끝에 추가하고, `InsertSubtitle`로 섹션에 자막 노드를 이어 붙인다. `PrintSection`은 특정 섹션 번호의 자막 목록을 출력한다. 섹션 헤더(`SectionListNode`)는 섹션 번호와 자막 노드 리스트의 `head`/`tail` 포인터를 보관한다.

* **`Manager` 클래스** – 프로그램의 구동을 담당한다. `Run()` 함수는 `command.txt`를 열어 한 줄씩 명령을 읽고, 각 명령에 따라 위 자료구조를 생성/조작한 뒤 로그를 출력한다. 명령어 해석 중 오류가 발생하거나 인수가 잘못된 경우에는 정의된 에러 코드를 `log.txt`에 출력한다.

---

## 지원 명령어

`command.txt`에 기록할 수 있는 주요 명령어는 다음과 같다. 각 명령의 실행 결과와 오류 상황은 `log.txt`에 기록된다.

| 명령어                                             | 설명                                                                                                                      |
| ----------------------------------------------- | ----------------------------------------------------------------------------------------------------------------------- |
| `LOAD`                                          | `subtitle.txt`를 읽어 `SubtitleQueue`에 자막을 저장한다. 이미 데이터가 적재되어 있으면 에러를 출력한다.                                                |
| `QPOP`                                          | 큐에 저장된 모든 자막을 하나씩 꺼내 `SubtitleBST`에 삽입한다. BST가 아직 생성되지 않았으면 동적 할당한다. 데이터가 없을 경우 오류이다.                                   |
| `PRINT`                                         | 인수가 없는 경우 BST 전체를 중위 순회하여 시간 순으로 출력한다. `PRINT <section_num>` 형태로 쓰면 `SectionList`에서 해당 섹션 번호의 자막 목록을 출력한다.              |
| `SECTION <section_num> <start_time> <end_time>` | 주어진 섹션 번호의 섹션 헤더를 `SectionList`에 추가하고, BST에서 `[start_time, end_time]` 범위의 노드를 탐색하여 해당 섹션에 저장한다. 탐색된 노드가 없으면 빈 섹션을 출력한다. |
| `DELETE EQUAL <time>`                           | BST에서 지정된 시간과 동일한 자막을 모두 삭제한다.                                                                                          |
| `DELETE UNDER <time>`                           | BST에서 지정된 시간보다 작은 자막을 모두 삭제한다.                                                                                          |
| `EXIT`                                          | 동적으로 할당된 자료구조를 모두 해제하고 프로그램을 종료한다.                                                                                      |

섹션 명령의 구현에서는 `SubtitleBST`가 직접 `SectionList`에 노드를 넘겨주지 않도록, 임시 버퍼 큐를 두어 Manager를 통해 데이터를 전달한다. 이 방식은 클래스 간 의존성을 낮춰 향후 모듈 재사용을 용이하게 한다는 장점이 있다.

---

## 파일 구성

프로젝트는 아래와 같은 파일 구조를 갖는다. C++ 소스 파일 외에도 명령어, 자막 데이터 및 로그 파일을 포함하고 있다.

```bash
DS_2024_project1/
├─ Manager.cpp / Manager.h             # 명령어를 해석하고 자료구조를 제어하는 클래스
├─ SubtitleQueue.cpp / SubtitleQueue.h # 자막 큐 및 노드 구현
├─ SubtitleBST.cpp / SubtitleBST.h     # 이진 검색 트리 및 노드 구현
├─ SectionList.cpp / SectionList.h     # 섹션 리스트와 헤더/내용 노드 구현
├─ Time.cpp / Time.h                   # 시간 형식 클래스 정의 및 연산자 오버로딩
├─ basicheader.h                       # 공용 typedef(Datapair)와 include 모음
├─ main.cpp                            # 프로그램 진입점 – Manager::Run() 호출
├─ command.txt                         # 예시 명령어 집합
├─ subtitle.txt                        # 예시 자막 데이터 (시간, 내용)
├─ subtitleload.txt                    # 대량 테스트용 자막 파일
├─ log.txt                             # 프로그램 실행 후 생성되는 로그 파일
├─ Makefile                            # `make` 명령으로 전체 소스 빌드 (g++ –std=c++11)
├─ others/                             # 자료구조 실습용 참고 파일(bst, linkedList, queue)
└─ testbench/                          # 테스트용 입력/출력 파일 모음 (옵션)
```

---

## 빌드 및 실행 방법 (Linux)

```bash
# 프로젝트 루트 디렉토리로 이동
cd DS_2024_project1

# 컴파일 (실행파일: run)
make

# command.txt를 인자로 하여 실행
./run command.txt
```

---

## 예시 실행

`command.txt`와 `subtitle.txt`에 예시 데이터를 넣고 실행하면, `log.txt`에 다음과 같은 결과가 기록된다. 예를 들어, 아래 명령어를 수행할 경우:

```bash
LOAD
QPOP
PRINT
SECTION 3 00:52:10 00:52:30
SECTION 2 00:53:50 00:54:23
PRINT 3
PRINT 2
DELETE EQUAL 00:52:36
PRINT
DELETE UNDER 00:52:23
PRINT
PRINT 3
EXIT
```

생성된 `log.txt`는 다음과 같이 각 명령의 성공 여부와 데이터 상태를 보여 준다(일부 생략). `LOAD` 명령은 큐에 자막을 적재하고, `QPOP` 이후 `SubtitleBST`에 노드가 삽입되어 `PRINT` 명령에서 시간 순으로 출력됨을 확인할 수 있다. `SECTION` 명령은 지정한 시간 구간을 구분된 섹션에 저장하고, `DELETE` 명령은 해당 조건에 맞는 자막을 BST에서 삭제한다.

```text
===== LOAD =====
01:03:45 - You're not listening to me!
00:52:36 - You're welcome.
... (중략) ...
01:11:41 - My real parents. And... the eyes of the children.
===============

===== QPOP =====
Success
===============

===== PRINT =====
Subtitle_BST
00:21:37 - See you soon.
00:52:19 - I'm going to bed.
... (중략) ...
01:11:54 - If I lose, I'll stay here with you forever
01:11:59 - And I'll let you sew buttons into my eyes.
===============

===== SECTION =====
Success
===============

===== PRINT =====
Section 3
00:52:19 - I'm going to bed.
00:52:20 - Right now!
... (중략) ...
===============

... 이하 생략 ...
```

---

## 느낀점 및 개선 사항

프로젝트를 진행하면서 세 자료구조가 서로 직접적으로 데이터를 주고받지 않도록 설계하는 것이 가장 어려웠다. 특히 `SECTION` 명령 구현 시 `SubtitleBST`에서 찾은 노드를 바로 `SectionList`에 삽입할 수 없기 때문에, 임시 큐 버퍼를 두어 `Manager`를 통해 전달하도록 설계하였다. 이러한 방식은 모듈 간 결합도를 낮추어 각 클래스가 독립적으로 재사용될 수 있도록 해 주었다.

또한 시간 비교 연산을 수행하는 `Time` 클래스를 별도의 헤더로 분리하고 연산자 오버로딩을 적용함으로써 프로젝트 전반의 코드를 간결하게 유지할 수 있었다. 자료구조와 알고리즘을 실습하면서 메모리 관리와 예외 처리의 중요성을 깨달았고, Visual Studio와 GitHub를 연동하여 버전 관리를 체계적으로 수행하는 경험을 쌓을 수 있었다.
