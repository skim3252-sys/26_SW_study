# Week 01 - C++ Class / Project Structure

## 1. `struct`와 `class`

- `struct`와 `class` 모두 멤버 변수, 멤버 함수, 생성자를 가질 수 있다.
- 기본 접근 지정자가 다르다.
  - `struct` → `public`
  - `class` → `private`
- 생성자가 없는 단순 aggregate 타입은 `{}`를 사용해 멤버 선언 순서대로 초기화할 수 있다.

```cpp
struct VehicleState {
    double speed;
    double steeringAngle;
    double acceleration;
    double brake;
};

VehicleState state{60.0, 10.0, 2.0, 0.0};
```

위 코드는 다음 순서로 초기화된다.

```text
60.0 → speed
10.0 → steeringAngle
2.0  → acceleration
0.0  → brake
```

생성자를 직접 정의한 경우 `{}`는 정의된 생성자를 호출하는 형태로 사용할 수 있다.

---

## 2. Encapsulation과 Setter

`VehicleState`를 `Vehicle` 클래스의 `private` 멤버로 두면 외부에서 상태를 직접 변경할 수 없다.

```cpp
class Vehicle {
private:
    VehicleState state;
};
```

따라서 setter를 통해 상태를 변경하도록 만들 수 있다.

```cpp
void Vehicle::setSpeed(double newSpeed)
{
    state.speed = validateSpeed(newSpeed);
}
```

이렇게 하면 객체 상태를 변경하기 전에 유효성 검사를 수행할 수 있다.

```text
외부 입력
   ↓
Setter
   ↓
Validation
   ↓
VehicleState 변경
```

---

## 3. Constructor와 Member Initializer List

생성자 본문에서 값을 대입하는 것과 멤버 초기화 리스트를 사용하는 것은 다르다.

### 생성 후 대입

```cpp
Vehicle::Vehicle(double speed)
{
    state.speed = speed;
}
```

이 방식은 `state`가 먼저 생성된 후 값을 다시 대입한다.

```text
state 생성
↓
기본값 설정
↓
생성자 body 실행
↓
값 대입
```

### Member Initializer List

```cpp
Vehicle::Vehicle(double speed)
    : state{speed, 0.0, 0.0, 0.0}
{
}
```

이 방식은 `state`를 원하는 값으로 처음부터 초기화한다.

```text
값 계산 또는 Validation
↓
state를 해당 값으로 바로 생성
```

`const` 멤버나 reference 멤버는 생성되는 순간 값이나 참조 대상이 결정되어야 하므로 초기화 리스트가 필요하다.

---

## 4. 생성자 초기화와 Validation

잘못된 값으로 먼저 초기화한 뒤 setter로 수정하는 것보다, 검증된 값으로 처음부터 초기화하는 것이 더 깔끔하다.

```cpp
Vehicle::Vehicle(
    double speed,
    double steeringAngle,
    double acceleration,
    double brake
)
    : state{
        validateSpeed(speed),
        validateSteeringAngle(steeringAngle),
        acceleration,
        validateBrake(brake)
    }
{
}
```

예를 들어 다음과 같이 객체를 생성해도:

```cpp
Vehicle car(-100.0, 90.0, -2.5, 5.0);
```

`state`는 처음부터 검증된 값으로 생성된다.

```text
speed         → 0.0
steeringAngle → 30.0
acceleration  → -2.5
brake         → 1.0
```

---

## 5. `static` Member Function

`static` 멤버 함수는 특정 객체에 속하지 않고 클래스 자체에 속한다.

```cpp
class Vehicle {
private:
    static double validateSpeed(double speed);
};
```

특징:

- 특정 `Vehicle` 객체에 의존하지 않는다.
- `this` 포인터가 없다.
- 객체 생성 없이 `Vehicle::validateSpeed()` 형태로 호출할 수 있다.
- 특정 객체의 일반 멤버 변수에 직접 접근할 수 없다.
- 객체 상태와 무관한 validation 로직 등에 적합하다.
- 생성자 초기화 리스트에서도 사용할 수 있다.

전역 함수처럼 특정 객체에 귀속되지는 않지만, `Vehicle`이라는 클래스의 책임 안에 묶여 있는 함수라고 생각할 수 있다.

`static`은 클래스 선언부에 작성하고 구현부에서는 다시 작성하지 않는다.

```cpp
// Vehicle.hpp
static double validateSpeed(double speed);
```

```cpp
// Vehicle.cpp
double Vehicle::validateSpeed(double speed)
{
    if (speed < 0.0) {
        return 0.0;
    }

    if (speed > 200.0) {
        return 200.0;
    }

    return speed;
}
```

---

## 6. `this`

`this`는 현재 멤버 함수를 호출한 객체를 가리키는 포인터다.

```cpp
this->speed
```

는 현재 객체의 `speed` 멤버를 의미한다.

```cpp
*this
```

는 현재 객체 자체를 의미한다.

일반 멤버 함수에는 `this`가 존재하지만 `static` 멤버 함수에는 특정 객체가 없으므로 `this`가 존재하지 않는다.

---

## 7. `const VehicleState& getState() const`

```cpp
const VehicleState& getState() const;
```

앞쪽 `const`와 뒤쪽 `const`의 의미는 다르다.

### 앞쪽 `const`

```cpp
const VehicleState&
```

- reference로 반환하여 불필요한 객체 복사를 피한다.
- 반환된 reference를 통해 원본 객체를 수정할 수 없다.

예:

```cpp
const VehicleState& state = car.getState();
```

이 경우 다음 코드는 불가능하다.

```cpp
state.speed = 100.0;
```

### 뒤쪽 `const`

```cpp
getState() const
```

- 해당 멤버 함수 내부에서 현재 객체의 상태를 변경하지 않음을 의미한다.
- 매개변수를 수정하지 못한다는 의미가 아니다.
- `this`가 가리키는 객체의 일반 멤버를 수정할 수 없다.

---

## 8. Header / Source Separation

C++ 프로젝트에서는 선언과 구현을 분리할 수 있다.

- `.hpp` → 타입과 함수의 선언
- `.cpp` → 함수의 실제 구현
- `main.cpp` → 선언된 타입과 기능을 사용하는 코드

현재 프로젝트 구조:

```text
main.cpp
   │
   └─ Vehicle.hpp
      → Vehicle이라는 타입과 사용 가능한 함수를 확인

Vehicle.cpp
   │
   └─ Vehicle.hpp
      → 자신이 구현해야 할 Vehicle의 선언을 확인
```

각 `.cpp` 파일은 서로의 내용을 자동으로 아는 것이 아니다.

`main.cpp`는 `Vehicle.cpp`를 직접 보는 것이 아니라 `Vehicle.hpp`에 작성된 선언을 통해 `Vehicle`의 존재와 인터페이스를 알게 된다.

---

## 9. Scope Resolution Operator `::`

헤더에서 선언한 클래스 멤버 함수를 `.cpp`에서 구현할 때 `::`를 사용한다.

```cpp
const VehicleState& Vehicle::getState() const
{
    return state;
}
```

`Vehicle::`는 해당 함수가 `Vehicle` 클래스에 속한 멤버 함수라는 의미다.

다른 예:

```cpp
void Vehicle::setSpeed(double newSpeed)
{
    state.speed = validateSpeed(newSpeed);
}
```

---

## 10. Default Arguments

기본 매개변수는 일반적으로 선언부에만 작성한다.

```cpp
// Vehicle.hpp

Vehicle(
    double speed = 0.0,
    double steeringAngle = 0.0,
    double acceleration = 0.0,
    double brake = 0.0
);
```

구현부에서는 기본값을 다시 작성하지 않는다.

```cpp
// Vehicle.cpp

Vehicle::Vehicle(
    double speed,
    double steeringAngle,
    double acceleration,
    double brake
)
    : state{
        validateSpeed(speed),
        validateSteeringAngle(steeringAngle),
        acceleration,
        validateBrake(brake)
    }
{
}
```

호출하는 코드에서는 헤더를 통해 함수 사용 방법을 확인하기 때문에 기본 매개변수 정보도 선언부에 둔다.

---

## 11. `#pragma once`

헤더 파일 맨 위에 다음과 같이 작성한다.

```cpp
#pragma once
```

같은 헤더 파일이 하나의 translation unit에서 여러 번 포함되어 `struct`나 `class`가 중복 정의되는 것을 방지한다.

예를 들어 `Vehicle.hpp`가 여러 경로를 통해 중복 include되더라도 실제 내용은 한 번만 포함되도록 한다.

---

## 12. 함수 선언과 함수 구현의 차이

헤더에서는 함수의 형태만 선언한다.

```cpp
void setSpeed(double newSpeed);
```

구현부에서는 실제 동작을 작성한다.

```cpp
void Vehicle::setSpeed(double newSpeed)
{
    state.speed = validateSpeed(newSpeed);
}
```

함수 구현 뒤에는 세미콜론이 필요하지 않다.

```cpp
void Vehicle::showState() const
{
}
```

반면 클래스나 struct 선언 끝에는 세미콜론이 필요하다.

```cpp
class Vehicle {
};
```

---

## 13. 현재 프로젝트 역할 분리

```text
Vehicle.hpp
├─ VehicleState 선언
├─ Vehicle 선언
├─ public interface
└─ private 멤버 및 함수 선언

Vehicle.cpp
├─ VehicleState 생성자 구현
├─ Vehicle 생성자 구현
├─ Getter / Setter 구현
├─ Validation 구현
└─ 출력 기능 구현

main.cpp
└─ Vehicle 객체를 생성하고 public interface 사용
```

이 구조를 통해 `main.cpp`는 `Vehicle` 내부 구현을 알 필요 없이 공개된 interface만 사용하면 된다.