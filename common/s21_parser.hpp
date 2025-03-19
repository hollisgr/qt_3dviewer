#ifndef S21_PARSER_HPP
#define S21_PARSER_HPP

#include <float.h>

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define S21_PI 3.14159265358979323846
#define MAX_VERTICES 1000000

namespace s21 {

/**
 * @brief Min-Max vertex position.
 *
 * Min-Max vertex position in Vector3D x, y, z.
 *
 */
typedef struct {
  double min_x;
  double min_y;
  double min_z;
  double max_x;
  double max_y;
  double max_z;
} Min_Max_t;

/**
 * @brief Class erorr handling.
 *
 * Class for error handling.
 *
 */
class s21_panic {
 public:
  enum { OK, INCORRECTFILE, INCORRECTDATA, MEMORYERROR };
  s21_panic() {}
  ~s21_panic() {}

  /**
   * @brief Checking error.
   *
   * Checking ID error, if not OK return panic.
   *
   * @param err ID error.
   */
  void check(int err);

  /**
   * @brief Panic!.
   *
   * Breaking Work if error not OK.
   *
   * @param err ID error.
   */
  void panic(int err);
};

/**
 * @brief Class handling *.obj files.
 *
 * Have funcs working with *.obj files.
 *
 */
class s21_obj {
 private:
  int v_array_size;
  int i_array_size;
  std::vector<double>* vertex_array;
  std::vector<int>* index_array;

 public:
  s21_obj();
  ~s21_obj();

  /**
   * @defgroup Rotation
   * Rotate figure on X, Y, Z.
   * @{
   */

  /**
   * @brief Rotate X.
   *
   * @param angle Angle rotation.
   */
  void s21_rotate_x(double angle);

  /**
   * @brief Rotate Y.
   *
   * @param angle Angle rotation.
   */
  void s21_rotate_y(double angle);

  /**
   * @brief Rotete Z.
   *
   * @param angle Angle rotation.
   */
  void s21_rotate_z(double angle);
  /** @} */

  /**
   * @brief Scaling figure.
   *
   * @param scale_value Scaling value.
   */
  void s21_scale(double scale_value);

  /**
   * @defgroup Movement
   * Moved figure on X, Y, Z.
   * @{
   */

  /**
   * @brief Move X.
   *
   * @param value Moved value.
   */
  void s21_move_x(double value);

  /**
   * @brief Move Y.
   *
   * @param value Moved value.
   */
  void s21_move_y(double value);

  /**
   * @brief Move Z.
   *
   * @param value Moved value.
   */
  void s21_move_z(double value);
  /** @} */

  /**
   * @defgroup Getter
   * @{
   */

  /**
   * @brief Get count vertex position on x, y, z.
   * @return Vertex size
   */
  int get_v_arrey_size() const;

  /**
   * @brief Get count index of vertex.
   * @return Index size
   */
  int get_i_arrey_size() const;

  /**
   * @brief Get vector of vertex.
   * @return Vector of vertex
   */
  std::vector<double>* get_vertex_array() const;

  /**
   * @brief Get vector of index.
   * @return Vector of index
   */
  std::vector<int>* get_index_array() const;

  /**
   * @brief Get vertex of i.
   * @return vertex value
   */
  double get_vertex_array(int i);

  /**
   * @brief Get index of i.
   * @return Index value
   */
  int get_index_array(int i);
  /** @} */

  /**
   * @defgroup Setter
   * @{
   */

  /**
   * @brief Set size vector of vertex.
   *
   * @param value vertex size.
   */
  void set_v_arrey_size(int value);

  /**
   * @brief Set size vector of index.
   *
   * @param value index size.
   */
  void set_i_arrey_size(int value);

  /**
   * @brief Set vertex value.
   *
   * @param value Vertex value.
   */
  void set_vertex_array(double value);

  /**
   * @brief Set index value.
   *
   * @param value inidex value.
   */
  void set_index_array(int value);
  /** @} */
};

/**
 * @brief Class parsing figure.
 */
class s21_parser {
 private:
  s21_obj* obj;
  s21_panic* error;

 public:
  s21_parser();
  ~s21_parser();

  /**
   * @brief Parsing edges.
   * @param str string with values.
   */
  void ParseEdge(std::string str);

  /**
   * @brief Parsing vertex.
   * @param str string with values.
   * @param lim min-max value.
   */
  void ParseVertex(std::string str, Min_Max_t* lim);

  /**
   * @brief Function of parsing.
   * @see ParseEdge
   * @see ParseVertex
   * @see ParsingFile
   * @param File obj file.
   */
  void ParseData(std::ifstream& File);

  /**
   * @brief Open *.obj file.
   * @param filename file name of obj.
   */
  s21::s21_obj* ParsingFile(char* filename);

  /**
   * @brief Function return figure.
   * @return return s21_obj
   */
  s21_obj* GetObj();
};

}  // namespace s21

#endif  // S21_PARSER