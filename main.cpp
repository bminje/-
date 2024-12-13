#include <iostream>
#include "ReservationManager.h"

using namespace std;

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
