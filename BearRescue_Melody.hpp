#pragma once

#include "Note.hpp"

/**
 * @brief Tracks and manages a collection of Notes to play in a melody
 *
 */
class Melody {
private:
  const Note *m_song;
  const uint8_t m_pin;
  const int m_size;
  unsigned long m_time;
  unsigned long m_prevTime;
  bool m_repeat;
  bool m_resume;

  int m_index;
  int m_prevIndex;
  int m_timeNext;

  const int timeScalar;

  inline double eqlTemp(int note) { return pow(2, note / 12.0) * 440; }

  inline void softReset() {
    m_index = 0;
    m_prevIndex = -1;
    m_time = 0;
    m_timeNext = m_song[m_index].duration();
  }

  void play();

public:
  /**
   * @brief Default constructor is disallowed
   *
   */
  Melody() = delete;

  /**
   * @brief Construct a new Melody object
   *
   * @param pin pin id where buzzer is connected
   * @param song pointer to first element of an array of Notes
   * @param size size of the given collection of Notes
   */
  Melody(const int pin, const Note *song, int size);

  /**
   * @brief Construct a new Melody object
   *
   * @param pin pin id where buzzer is connected
   * @param song pointer to first element of an array of Notes
   * @param size size of the given collection of Notes
   * @param repeat determines if the song will repeat or stop upon reaching the
   * end
   */
  Melody(const int pin, const Note *song, int size, bool repeat);

  /**
   * @brief Construct a new Melody object
   *
   * @param pin pin id where buzzer is connected
   * @param song pointer to first element of an array of Notes
   * @param size size of the given collection of Notes
   * @param repeat determines if the song will repeat or stop upon reaching the
   * end
   * @param bpm beats per minute of the song
   * @param baseBeat duration of the base note
   */
  Melody(const int pin, const Note *song, int size, bool repeat, int bpm,
         int baseBeat);

  // default destructor

  /**
   * @brief advance and play the corresponding note while updating time
   *
   */
  void advance();

  /**
   * @brief pause current execution so that when play is executed next the time
   * delta gets reset
   *
   */
  void pause();

  /**
   * @brief reset the current playing song to the beginning
   *
   */
  void reset();

  /**
   * @brief get current time
   *
   * @return int representing beat relative to melody rhythm
   */
  int time() { return m_time; }
};

void Melody::play() {
  if (m_song[m_index].isPitch()) {
    int pitch = m_song[m_index].pitch();
    if (m_index != m_prevIndex) {
      tone(m_pin, eqlTemp(pitch));
    }
  } else {
    noTone(m_pin);
  }
}

Melody::Melody(const int pin, const Note *song, int size)
    : m_pin(pin), m_song(song), m_size(size), m_repeat(true), m_time(0),
      m_resume(true), m_index(0), timeScalar(32 * 128) {
  m_timeNext = m_song[m_index].duration();
  m_prevIndex = -1;
  m_prevTime = millis();
}

Melody::Melody(const int pin, const Note *song, int size, bool repeat)
    : m_pin(pin), m_song(song), m_size(size), m_repeat(repeat), m_time(0),
      m_resume(true), m_index(0), timeScalar(32 * 128) {
  m_timeNext = m_song[m_index].duration();
  m_prevIndex = -1;
  m_prevTime = millis();
}

inline Melody::Melody(const int pin, const Note *song, int size, bool repeat,
                      int bpm, int baseBeat)
    : m_pin(pin), m_song(song), m_size(size), m_repeat(repeat), m_time(0),
      m_resume(true), m_index(0), timeScalar(baseBeat * bpm) {
  m_timeNext = m_song[m_index].duration();
  m_prevIndex = -1;
  m_prevTime = millis();
}

inline void Melody::advance() {
  const double BEAT_UNIT = timeScalar / 60000.0;
  unsigned long now = millis();
  if (m_prevIndex < 0) {
    m_prevTime = now;
  }
  unsigned long timeDelta = now - m_prevTime;
  m_prevTime = now;

  if (m_resume) {
    // prevents time jumping from a prolonged delay
    m_resume = false;
  } else {
    m_time += timeDelta;

    if (static_cast<int>(BEAT_UNIT * m_time) < m_timeNext) {
      // play current note
      play();
    } else if (m_size - m_index > 1) {
      // move to next note
      m_index += 1;
      m_timeNext += m_song[m_index].duration();
      play();
    } else if (m_repeat) {
      // song has ended so loop here
      softReset();
      play();
    } else {
      // play has ended
      noTone(m_pin);
    }
  }

  m_prevIndex = m_index;
}

inline void Melody::pause() {
  m_resume = true;
  noTone(m_pin);
}

inline void Melody::reset() {
  softReset();
  m_resume = true;
  noTone(m_pin);
}
