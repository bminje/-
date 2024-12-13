#ifndef RESERVATIONMANAGER_H
#define RESERVATIONMANAGER_H

#include <vector>
#include <memory>
#include "Reservation.h" // Reservation 헤더 포함

using namespace std;

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

    // 예약된 강의실을 확인하는 함수
    vector<string> getAvailableRooms(const string& requestedTime) const {
        vector<string> availableRooms; // 예약 가능한 강의실 목록
        vector<string> allRooms = {"101", "102", "103", "104", "105"}; // 전체 강의실 목록

        // 모든 강의실에 대해 반복
        for (const auto& room : allRooms) {
            bool isAvailable = true; // 강의실의 예약 가능 여부

            // 요청한 시간에 예약된 강의실 확인
            for (const auto& reservation : reservedRooms) {
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
};

#endif // RESERVATIONMANAGER_H
