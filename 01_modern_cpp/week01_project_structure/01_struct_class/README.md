static 멤버 함수는 객체에 의존 X , Vehicle::validateSpeed() 로 호출 가능 때문에 생성자 초기화에서도 호출 가능

Setter 설정 -> 유효성 검증이 가능 

앞 const 와  뒤 const 의 차이 -> 참조를 통한 수정 X / 메소드 내부에서 객체의 상태 수정 X