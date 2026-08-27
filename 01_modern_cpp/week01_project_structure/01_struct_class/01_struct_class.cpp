#include <iostream>

using namespace std;
struct VehicleState {

	double speed = 0.0;
	double steeringAngle = 0.0;
	double acceleration = 0.0;
	double brake = 0.0;

	VehicleState(double speed = 0.0,
		double steeringAngle = 0.0,
		double acceleration = 0.0,
		double brake = 0.0)
		: speed(speed), steeringAngle(steeringAngle), acceleration(acceleration), brake(brake) {
		cout << "VehicleState constructor called." << endl;
	}
};
// 앞 const 와  뒤 const 의 차이 -> 참조를 통한 수정 X / 메소드 내부에서 객체의 상태 수정 X
class Vehicle {
public:
	Vehicle(double speed = 0.0,
		double steeringAngle = 0.0,
		double acceleration = 0.0,
		double brake = 0.0)
		: state{ speed, steeringAngle, acceleration, brake }
		// struct, class 생성자 없이도 멤버 변수 순서대로 초기화 O (public 멤버 변수만 가능)
	{

		setSpeed(speed);
		setSteeringAngle(steeringAngle);
		setAcceleration(acceleration);
		setBrake(brake);
	}
	void showState(void) const {
		cout << "Speed: " << state.speed << endl;
		cout << "Steering Angle: " << state.steeringAngle << endl;
		cout << "Acceleration: " << state.acceleration << endl;
		cout << "Brake: " << state.brake << endl;
	}
	const VehicleState& getState(void) const {
		return state;
	}
	// Setter -> 유효성 검증이 가능 
	void setSpeed(double newSpeed) {
		state.speed = validateSpeed(newSpeed);
	}
	void setSteeringAngle(double newSteeringAngle) {
		state.steeringAngle = validateSteeringAngle(newSteeringAngle);
	}
	void setAcceleration(double newAcceleration) {
		state.acceleration = newAcceleration;
	}
	void setBrake(double newBrake) {
		state.brake = validateBrake(newBrake);
	}

private:
	VehicleState state;
	//static 멤버 함수는 객체에 의존 X , Vehicle::validateSpeed() 로 호출 가능
	// 때문에 생성자 초기화에서도 호출 가능
	static double validateSpeed(double speed) {
		if (speed < 0.0) {
			cout << "Speed cannot be negative. Setting speed to 0." << endl;
			return 0.0;
		}
		else if (speed > 200.0) {
			cout << "Speed cannot exceed 200. Setting speed to 200." << endl;
			return 200.0;	
		}
		else {
			return speed;
		}
	}
	static double validateSteeringAngle(double steeringAngle) {
		if (steeringAngle < -45.0) {
			cout << "Steering angle cannot be less than -45 degrees. Setting to -45." << endl;
			return -45.0;
		}
		else if (steeringAngle > 45.0) {
			cout << "Steering angle cannot exceed 45 degrees. Setting to 45." << endl;
			return 45.0;	
		}
		else {
			return steeringAngle;
		}
	}
		static double validateBrake(double brake) {
			if (brake < 0.0) {
				return 0.0;
			}
			else if (brake > 1.0) {
				return 1.0;
			}
			else {
				return brake;
			}
		}
	};

	int main(void) {
		//Vehicle myCar;
		//myCar.setSpeed(60.0);
		//myCar.setSteeringAngle(15.0);
		//myCar.setAcceleration(3.5);
		//myCar.setBrake(0.0);
		//const VehicleState& state = myCar.getState();
		//cout << "Vehicle State:" << endl;
		//cout << "Speed: " << state.speed << endl;
		//cout << "Steering Angle: " << state.steeringAngle << endl;
		//cout << "Acceleration: " << state.acceleration << endl;
		//cout << "Brake: " << state.brake << endl;


		//myCar.setSpeed(-10.0); // 유효성 검증 테스트
		VehicleState initialState{ 50.0, 10.0, 2.0, 0.0 };
		return 0;

	}
