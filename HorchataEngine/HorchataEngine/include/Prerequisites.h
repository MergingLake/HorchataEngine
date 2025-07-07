#pragma once

// ============================================================================
// Standard Libraries
// ============================================================================
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <thread>
#include <map>
#include <fstream>
#include <unordered_map>

// ============================================================================
// Third-Party Libraries
// ============================================================================
#include <SFML/Graphics.hpp>
#include "Memory/TsharedPointer.h"
#include "Memory/TWeakPointer.h"
#include "Memory/TStaticPtr.h"
#include "Memory/TUniquePtr.h"

// ============================================================================
// Macros
// ============================================================================

/**
 * @brief Safely deletes a pointer and sets it to nullptr.
 * @param x Pointer to delete.
 */
#define SAFE_PTR_RELEASE(x) \
  if (x != nullptr) { delete x; x = nullptr; }

 /**
  * @brief Displays a message about a class method's resource creation state.
  * @param classObj Class name or object.
  * @param method Name of the method.
  * @param state Description of the state (e.g., "SUCCESS", "FAILED").
  */
#define MESSAGE(classObj, method, state)                            \
{                                                                   \
  std::ostringstream os_;                                           \
  os_ << classObj << "::" << method << " : "                        \
      << "[CREATION OF RESOURCE: " << state << "]\n";               \
  std::cerr << os_.str();                                           \
}

  /**
   * @brief Displays an error message and exits the program.
   * @param classObj Class name or object.
   * @param method Name of the method.
   * @param errorMSG Description of the error.
   */
#define ERROR(classObj, method, errorMSG)                           \
{                                                                   \
  std::ostringstream os_;                                           \
  os_ << "ERROR : " << classObj << "::" << method << " : "          \
      << "Error in data from params [" << errorMSG << "]\n";        \
  std::cerr << os_.str();                                           \
  exit(1);                                                          \
}

   // ============================================================================
   // Enumerations
   // ============================================================================

   /**
    * @enum ShapeType
    * @brief Represents types of shapes that can be created and rendered.
    */
enum ShapeType {
  EMPTY = 0, /**< No shape.                        */
  CIRCLE = 1, /**< Circle shape.                    */
  RECTANGLE = 2, /**< Rectangle shape.                 */
  TRIANGLE = 3, /**< Triangle shape (custom polygon). */
  POLYGON = 4  /**< Arbitrary polygon shape.         */
};
