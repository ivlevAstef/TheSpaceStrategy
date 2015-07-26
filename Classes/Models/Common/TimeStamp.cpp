#include "TimeStamp.h"

using namespace Common;

TimeStamp TimeStamp::now() {
  return TimeStamp();
}

TimeStamp TimeStamp::after(Seconds seconds) {
  return TimeStamp() + seconds;
}

TimeStamp::TimeStamp() {
  m_timestamp = std::chrono::system_clock::now();
}

TimeStamp::Seconds TimeStamp::deltaTime(const TimeStamp& t1, const TimeStamp& t2) {
  return t1.deltaTime(t2);
}

TimeStamp::Seconds TimeStamp::deltaTime(/*now*/) const {
  auto now = TimeStamp();
  return deltaTime(now);
}

TimeStamp::Seconds TimeStamp::deltaTime(const TimeStamp& timeStamp) const {
  auto milisec = std::chrono::duration_cast<std::chrono::milliseconds>(timeStamp.m_timestamp - m_timestamp).count();

  return (Seconds)milisec / 1000.0;
}

TimeStamp& TimeStamp::operator+=(Seconds seconds) {
  auto milisec = std::chrono::milliseconds((long long)(seconds * 1000.0));

  m_timestamp += milisec;

  return *this;
}
TimeStamp TimeStamp::operator+(Seconds seconds) const {
  TimeStamp res = TimeStamp();
  auto milisec = std::chrono::milliseconds((long long)(seconds * 1000.0));

  res.m_timestamp = m_timestamp + milisec;

  return res;
}

bool TimeStamp::operator<(const TimeStamp& timestamp) const {
  return m_timestamp < timestamp.m_timestamp;
}
bool TimeStamp::operator<=(const TimeStamp& timestamp) const {
  return m_timestamp < timestamp.m_timestamp;
}
bool TimeStamp::operator>(const TimeStamp& timestamp) const {
  return m_timestamp > timestamp.m_timestamp;
}
bool TimeStamp::operator>=(const TimeStamp& timestamp) const {
  return m_timestamp > timestamp.m_timestamp;
}