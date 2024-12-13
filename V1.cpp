#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <memory> // 스마트 포인터 사용을 위한 헤더

using namespace std;

// 예약 정보를 저장하는 추상 클래스
class Reservation {
public:
    string roomName; // 강의실 이름
    string timeSlot; // 예약 시간대 (예: "09:00-10:00")

    Reservation(const string& rName, const string& tSlot) 
        : roomName(rName), timeSlot(tSlot) {} // 생성자

    // 순수 가상 함수: 예약 정보를 출력하는 함수
    virtual void print() const = 0;

    virtual ~Reservation() {} // 가상 소멸자
};

// VIP 예약 정보를 저장하는 클래스
class VIPReservation : public Reservation {
public:
    string vipName; // VIP 고객 이름

    VIPReservation(const string& rName, const string& tSlot, const string& vName)
        : Reservation(rName, tSlot), vipName(vName) {} // 생성자

    // 예약 정보를 출력하는 가상 함수 오버라이드
    void print() const override {
        cout << "VIP 예약: " << vipName << ", 강의실: " << roomName << ", 시간: " << timeSlot << endl;
    }
};

// 제네릭 클래스를 사용하여 예약 정보를 저장하는 클래스
template<typename T>
class ReservationManager {
private:
    vector<unique_ptr<T>> reservedRooms; // 스마트 포인터를 사용한 포인터 배열

public:
    // 예약 추가 함수
    void addReservation(T* reservation) {
        reservedRooms.emplace_back(reservation); // 동적 객체를 스마트 포인터로 저장
    }

    // 예약 정보를 출력하는 함수
    void printReservations() const {
        for (const auto& reservation : reservedRooms) {
            reservation->print(); // 각 예약의 print() 호출
        }
    }

    // 예약 정보를 파일에 저장하는 함수
    void saveReservations(const string& filename) const {
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "예약 파일을 저장할 수 없습니다." << endl;
            return;
        }

        for (const auto& reservation : reservedRooms) {
            if (dynamic_cast<VIPReservation*>(reservation.get())) {
                file << "VIP " << reservation->roomName << " " << reservation->timeSlot << " " 
                     << static_cast<VIPReservation*>(reservation.get())->vipName << endl; // VIP 예약 정보 저장
            } else {
                file << reservation->roomName << " " << reservation->timeSlot << endl; // 일반 예약 정보 저장
            }
        }
        file.close(); // 파일 닫기
    }
};

// 빈 강의실 조회 함수
vector<string> getAvailableRooms(const ReservationManager<Reservation>& manager, const string& requestedTime) {
    vector<string> availableRooms; // 예약 가능한 강의실 목록
    vector<string> allRooms = {"101", "102", "103", "104", "105"}; // 전체 강의실 목록

    // 모든 강의실에 대해 반복
    for (const auto& room : allRooms) {
        bool isAvailable = true; // 강의실의 예약 가능 여부

        // 요청한 시간에 예약된 강의실 확인
        for (const auto& reservation : manager.reservedRooms) {
            if (reservation->roomName == room && reservation->timeSlot == requestedTime) {
                isAvailable = false; // 예약된 경우 false로 설정
                break; // 더 이상 확인할 필요 없음
            }
        }
        if (isAvailable) {
            availableRooms.push_back(room); // 예약 가능한 강의실 목록에 추가
        }
    }
    return availableRooms; // 예약 가능한 강의실 목록 반환
}

// 운영 시간 체크 함수
bool isWithinOperatingHours(const string& timeSlot) {
    return timeSlot >= "09:00" && timeSlot <= "18:00"; // 운영 시간 내 여부 확인
}

// 프로그램 실행 함수
int main() {
    ReservationManager<Reservation> manager; // 예약 관리 객체 생성

    // 예약 추가 예시 (이 부분은 실제 예약 추가 로직으로 대체 가능)
    manager.addReservation(new Reservation("101", "09:00-10:00"));
    manager.addReservation(new VIPReservation("102", "10:00-11:00", "John Doe"));

    // 예약 정보 출력
    cout << "현재 예약 목록:" << endl;
    manager.printReservations();

    // 예약 정보를 파일에 저장
    manager.saveReservations("reservations.txt");

    return 0; // 프로그램 종료
}
