#ifndef RESERVATION_H
#define RESERVATION_H

#include <iostream>
#include <string>

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

#endif // RESERVATION_H
