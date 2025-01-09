### **Corewar 게임 사용자 설명서**

Corewar은 두 개 이상의 프로그램이 가상 머신 환경에서 서로 경쟁하는 전투 게임입니다. 각 프로그램은 **워리어**라고 불리며, 다양한 명령어를 사용하여 상대방을 공격하거나 방어하며 살아남는 것이 목표입니다. 이 설명서는 **Corewar**의 게임 방식과 이를 플레이하는 방법을 이해할 수 있도록 돕기 위해 작성되었습니다.

---

### **1. 게임 목표**

게임의 목표는 간단합니다. 각 워리어는 다른 워리어의 프로그램을 무력화하고 **생존**해야 합니다. 이를 위해 워리어는 주어진 명령어들을 사용하여 상대 프로그램의 **메모리 영역**을 공격하고, **자신의 코드**가 실행되도록 해야 합니다.

- 게임이 종료되는 조건은 하나의 워리어가 모든 다른 워리어를 **죽이는 것**입니다.
- 게임은 **상대방의 프로세스**를 멈추게 하거나, **게임의 메모리 공간**에서 사라지도록 만들면서 진행됩니다.

---

### **2. 기본 개념**

#### **프로그램 구조**
Corewar 프로그램은 **어셈블리 언어**로 작성됩니다. 각 프로그램은 여러 명령어를 포함하고 있으며, 각 명령어는 가상 머신에서 실행됩니다. 명령어들은 특정 **메모리 주소**에서 실행되며, 이 주소들은 **원형 메모리**를 기반으로 구성됩니다. 

- **메모리**는 순차적이지 않고, 끝에서 다시 처음으로 돌아가는 원형 구조입니다. 예를 들어, 메모리의 마지막 주소 다음은 첫 번째 주소로 이어집니다.

#### **명령어**
Corewar의 프로그램은 다음과 같은 **명령어들**을 사용하여 행동합니다:

- `live`: 프로그램이 살아있음을 알리는 명령어입니다. 프로그램은 이 명령어로 상대방을 추적하거나 자신의 생존을 알릴 수 있습니다.
- `ld`: 값을 레지스터에 로드하는 명령어입니다. 주로 메모리에서 값을 읽어와서 **레지스터**에 저장합니다.
- `st`: 값을 레지스터에서 메모리로 저장하는 명령어입니다.
- `add`, `sub`: 두 레지스터 값을 더하거나 빼는 명령어입니다.
- `and`, `or`, `xor`: 비트 연산을 통해 값을 결합하거나 변경합니다.
- `zjmp`: 특정 조건에서 **점프**를 수행하여 다른 메모리 주소로 이동하는 명령어입니다.
- `fork`, `lfork`: 새로운 프로세스를 생성하는 명령어로, 게임의 전략을 확장합니다.
- `aff`: 레지스터의 값을 화면에 출력하는 명령어로, 주로 디버깅용으로 사용됩니다.

#### **명령어 구조**
명령어는 기본적으로 **인자**를 가질 수 있으며, 각 인자는 특정 **타입**과 **형식**을 따릅니다. 예를 들어:

- `T_REG`: 레지스터 타입
- `T_DIR`: 직접 주소 타입
- `T_IND`: 간접 주소 타입

각 명령어는 몇 개의 인자를 가지고 있으며, 각 인자는 지정된 타입에 맞춰야 합니다. 예를 들어, `ld` 명령어는 두 개의 인자를 가지며, 첫 번째 인자는 **디렉토리 주소**나 **간접 주소**일 수 있고, 두 번째 인자는 **레지스터**여야 합니다.

---

### **3. 게임 진행**

Corewar는 **프로세스**들이 서로 경쟁하는 방식으로 진행됩니다. 각 프로세스는 메모리에서 독립적으로 실행되며, **프로그램**이 지정된 명령어들을 실행하여 상대 프로그램을 방어하거나 공격합니다.

#### **1. 초기화**
게임이 시작되면, 각 프로그램(워리어)은 **메모리의 일정 공간**에 배치됩니다. 프로그램의 명령어들은 이 공간에서 순차적으로 실행되며, 각 명령어는 메모리에서 **차례대로** 실행됩니다.

#### **2. 명령어 실행**
각 프로그램은 `g_inst` 배열에 정의된 명령어를 따라 실행됩니다. 예를 들어:

- `live` 명령어가 실행되면, 해당 프로그램은 살아있다는 메시지를 시스템에 전파합니다.
- `ld` 명령어는 메모리에서 값을 읽어 레지스터에 저장합니다.
- `zjmp` 명령어는 조건을 만족하면 다른 메모리 위치로 **점프**하여 새로운 명령어를 실행하게 만듭니다.

이와 같은 방식으로 각 프로그램은 서로 다르게 전략을 세우며 실행됩니다.

#### **3. 공격과 방어**
각 프로그램은 상대방을 공격하거나 방어하기 위해 다양한 명령어를 사용합니다. 예를 들어:

- `add`, `sub` 명령어는 레지스터 값을 조작하여 **연산을 수행**합니다.
- `and`, `or`, `xor` 명령어는 **비트 연산**을 통해 공격이나 방어를 할 수 있습니다.
- `fork`와 `lfork`는 새로운 프로세스를 생성하여 공격을 **확장**하거나 **다각화**합니다.

게임 진행 중, 각 프로그램은 상대방의 패턴을 분석하고 그에 맞는 공격을 준비해야 합니다. 예를 들어, 상대방이 일정한 패턴으로 **live** 명령어를 반복하면, 그에 대한 **반격 전략**을 세울 수 있습니다.

#### **4. 프로세스 복제**
`fork`와 `lfork` 명령어는 **새로운 프로세스를 생성**합니다. `fork`는 상대방을 공격할 수 있는 또 다른 프로세스를 만들어내고, `lfork`는 더 가까운 주소에서 **프로세스를 복제**하여 상대를 추적합니다.

#### **5. 게임 종료**
게임은 **한 프로그램**이 **모든 프로그램을 죽였을 때** 종료됩니다. 프로그램이 상대방을 **무력화**하거나 **죽인 상태**가 되면, 해당 프로그램이 승리하게 됩니다.

---

### **4. 게임 전략**

게임에서 승리하기 위해서는 전략이 중요합니다. 주로 다음과 같은 전략이 유효합니다:

- **패턴 분석**: 상대 프로그램이 사용하는 명령어 패턴을 분석하여 예측하고, 그에 맞는 반격을 준비합니다.
- **프로세스 분할**: `fork`나 `lfork`를 활용하여 여러 프로세스를 만들어 공격의 기회를 확장합니다.
- **조건부 점프**: `zjmp`를 활용하여 메모리 내에서 빠르게 **위치 이동**을 하여 공격을 피하거나 반격을 시도합니다.
- **비트 연산 활용**: `and`, `or`, `xor`와 같은 비트 연산을 활용하여 상대방의 메모리 공간을 **조작**하고 공격합니다.

---

### **5. 예시 프로그램**
마지막 라인은 비워두어야합니다.

``` asm
.name "Yeonguk"
.comment "ha go ship un mal English row"


ld %50, r3
ld %4, r16
ld %0, r2

hamsuu:
	st		r1, 6
	live	%214422161
	fork	%:gamsuu
	st		r1, 6
	live	%214422161
	ld		%190057743, r13
	ld		%-409, r14
	ld		%-21, r15
	ld		%214422161, r16
	zjmp	%:goooo

gamsuu:
	st		r1, 6
	live	%214422161
	ld		%269090790, r13
	ld		%-405, r14
	ld		%-17, r15
	ld		%214422161, r16
	zjmp	%:hamsuu


goooo:
	st r13, 8
	zjmp %3

```
