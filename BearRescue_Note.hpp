#pragma once

/**
 * @brief Manages a note and its attributes (type, duration, and pitch) within
 * an int with the following memory structure (little endian): 0-15 [duration],
 * 16-22 [pitch offset +54], 23 [type 1: note, 0: rest], 24-31 [reserved]
 *
 */
class Note {
private:
  unsigned int m_length : 16;
  unsigned int m_bitfield : 8;

public:
  /**
   * @brief Default constructor is disallowed
   *
   */
  Note() = delete;
  
  /**
   * @brief Construct a new Note object
   *
   * @param bitfield bitfield of properties where 0-15 is duration, 16-22 is
   * pitch, and 23 is type
   */
  Note(unsigned long bitfield);

  // default destructor

  /**
   * @brief Get the duration of this note
   *
   * @return int value that represents the duration of a note where a whole is
   * equal to 2 ^ 6 * 3 ^ 6. That way there is almost always an exact way to
   * convert to triplets.
   */
  int duration() const noexcept { return m_length; }

  /**
   * @brief Determine if this note is rest or pitch
   *
   * @return true if the note is not a pitch,
   * @return otherwise the note is a rest
   */
  bool isPitch() const noexcept { return (m_bitfield >> 7 & 0x1); }

  /**
   * @brief Get the pitch of this note
   *
   * @return int value between -54 and 73 where 0 represents 440 hz in equal
   * temperament
   */
  int pitch() const noexcept { return (m_bitfield & 0x7f) - 54; }

  /**
   * @brief Get the bitfield of this note
   *
   * @return int that represents the bitfield that contains the note properties
   */
  unsigned long getBitfield() const noexcept {
    return 0UL + m_bitfield << 16 | m_length;
  }
};

Note::Note(unsigned long bitfield)
    : m_length(bitfield & 0xffff), m_bitfield(bitfield >> 16) {}
