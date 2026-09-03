## Pointer와 Reference

### Pointer

포인터는 객체의 **주소값을 저장**한다.

```cpp
int a = 10;

int* p = &a;
```

- `&a` : `a`의 주소
- `int* p` : `int`의 주소를 저장하는 포인터
- `*p` : 포인터가 가리키는 실제 값

### Reference

참조는 기존 객체의 **별명(alias)** 처럼 동작한다.

```cpp
int a = 10;

int& r = a;

```
`r`은 `a`를 참조하므로 `r = 30`을 하면 원본 `a`도 30으로 변경된다.

### 차이 요약

```text
T* p = &a;
→ 주소를 저장하는 Pointer

T& r = a;
→ 기존 객체를 직접 참조하는 Reference
```

- Pointer는 주소를 저장하며 `*p`로 실제 값에 접근한다.
- Reference는 원본 객체를 직접 사용하는 것처럼 접근한다.
- 둘 다 원본 객체를 수정할 수 있다.

## explicit 생성자

인자 1개로 호출 가능한 생성자는 다른 타입에서 해당 클래스 타입으로
암시적 변환에 사용될 수 있다.

예:

```cpp
class Speed {
public:
    Speed(double value);
};
```

이 경우:

```cpp
Speed s = 100.0; <- 마치 static_cast<Speed>(100.0) 작동
```
explicit Speed(double value); 로 설정할 경우 암시적 변환 제한
```cpp
PrintSpeed(100.0);  <- X error 발생
```

대신 명시적으로 객체를 생성해야 한다.

```cpp
PrintSpeed(Speed{100.0});
```

### 정리

- `explicit` 없음  
  → 컴파일러가 생성자를 이용해 암시적 타입 변환 가능

- `explicit` 있음  
  → 암시적 타입 변환 차단
  → 개발자가 직접 객체 생성을 명시해야 함

```cpp
Speed s{100.0};                    // 가능
Speed s(100.0);                    // 가능
Speed s = 100.0;                   // explicit이면 불가능
static_cast<Speed>(100.0);         // 명시적 변환이므로 가능
```

`explicit`은 의도하지 않은 자동 타입 변환을 방지하여
코드의 타입 의도를 명확하게 해준다.