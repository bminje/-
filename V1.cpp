#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Reservation {
    string roomName;
    string timeSlot; // 예: "09:00-10:00"
};

// 이미 예약된 강의실 목록
vector<Reservation> reservedRooms = {
    {"101", "09:00-10:00"},
    {"102", "10:00-11:00"},
    {"103", "09:30-10:30"}
};

// 빈 강의실 조회
vector<string> getAvailableRooms(const string& requestedTime) {
    vector<string> availableRooms;
    vector<string> allRooms = {"101", "102", "103", "104", "105"};

    for (const auto& room : allRooms) {
        bool isAvailable = true;
        // 요청한 시간에 예약된 강의실 확인
        for (const auto& reservation : reservedRooms) {
            if (reservation.roomName == room && reservation.timeSlot == requestedTime) {
                isAvailable = false;
                break;
            }
        }
        if (isAvailable) {
            availableRooms.push_back(room);
        }
    }
    return availableRooms;
}

// 예약하기
void reserveRoom(const string& roomName, const string& timeSlot) {
    reservedRooms.push_back({roomName, timeSlot});
    cout << roomName << " 강의실이 " << timeSlot << "에 예약되었습니다." << endl;
}

// 운영 시간 체크
bool isWithinOperatingHours(const string& timeSlot) {
    return timeSlot >= "09:00" && timeSlot <= "18:00";
}

// 모든 강의실이 예약되었는지 체크
bool areAllRoomsFullyReserved() {
    vector<string> allRooms = {"101", "102", "103", "104", "105"};
    for (const auto& room : allRooms) {
        bool isRoomFullyReserved = true;
        for (const auto& reservation : reservedRooms) {
            if (reservation.roomName == room) {
                isRoomFullyReserved = false;
                break;
            }
        }
        if (!isRoomFullyReserved) {
            return false; // 하나라도 비어있으면 false
        }
    }
    return true; // 모든 강의실이 예약되었으면 true
}

// 프로그램 실행
int main() {
    while (true) {
        // 모든 강의실이 예약되었는지 확인
        if (areAllRoomsFullyReserved()) {
            cout << "모든 강의실이 예약되었습니다. 프로그램을 종료합니다." << endl;
            break;
        }

        string requestedTime;
        cout << "예약할 시간을 입력하세요 (예: 09:00-10:00) 또는 'exit'를 입력하여 종료: ";
        cin >> requestedTime;

        // 프로그램 종료 확인
        if (requestedTime == "exit") {
            cout << "프로그램을 종료합니다." << endl;
            break;
        }

        // 운영 시간 체크
        if (!isWithinOperatingHours(requestedTime.substr(0, 5))) {
            cout << "운영 시간은 09:00~18:00입니다. 다시 입력해 주세요." << endl;
            continue;
        }

        vector<string> availableRooms = getAvailableRooms(requestedTime);

        if (availableRooms.empty()) {
            cout << "예약할 수 있는 강의실이 없습니다." << endl;
        } else {
            string roomToReserve;
            while (true) {
                cout << "예약 가능한 강의실: ";
                for (const auto& room : availableRooms) {
                    cout << room << " ";
                }
                cout << endl;

                cout << "예약할 강의실을 선택하세요: ";
                cin >> roomToReserve;

                // 선택한 강의실이 예약 가능한 강의실 목록에 있는지 확인
                bool isRoomValid = false;
                for (const auto& room : availableRooms) {
                    if (room == roomToReserve) {
                        isRoomValid = true;
                        break;
                    }
                }

                // 이미 예약된 시간인지 확인
                bool isTimeAlreadyReserved = false;
                for (const auto& reservation : reservedRooms) {
                    if (reservation.roomName == roomToReserve && reservation.timeSlot == requestedTime) {
                        isTimeAlreadyReserved = true;
                        break;
                    }
                }

                if (isRoomValid && !isTimeAlreadyReserved) {
                    reserveRoom(roomToReserve, requestedTime);
                    break; // 예약 완료 후 루프 종료
                } else if (!isRoomValid) {
                    cout << "잘못된 강의실 선택입니다. 다시 선택해 주세요." << endl;
                } else if (isTimeAlreadyReserved) {
                    cout << "선택한 강의실은 이미 예약된 시간입니다. 다른 강의실을 선택해 주세요." << endl;
                }
            }
        }
    }

    return 0;
}
