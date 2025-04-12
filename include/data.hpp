#pragma once
#include <ctime>
#include <string>

struct Student {
    int id_student;
    std::string name;
    int year_registered;
    int id_class;

    Student(int id_student = 0, const std::string& name = "", int year = 0, int class_id = 0) {
        this->id_student = id_student;
        this->name = name;
        this->year_registered = year;
        this->id_class = class_id;
    }
};

struct PembayaranSPP {
    int id_student;
    std::string id_tagihan;
    double nominal;
    time_t timestamp;
    time_t deadline;
    bool is_paid;

    PembayaranSPP(int id_student = 0, int id_tagihan = 0, double nominal = 0, time_t timestamp = time(0), time_t deadline = 0, bool is_paid = false) {
        this->id_tagihan = id_tagihan;
        this->id_student = id_student;
        this->nominal = nominal;
        this->timestamp = timestamp;
        this->deadline = deadline;
        this->is_paid = is_paid;
    }

    bool is_overdue() const {
        return deadline > 0 && time(0) > deadline;
    }

    int days_remaining() const {
        if (deadline == 0) return 0;
        return (deadline - time(0)) / 86400;
    }
};