#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <camera/camera.hpp>
#include <glm/trigonometric.hpp>

Camera::Camera(GLFWwindow *window) {
  view = glm::mat4(1.0f);
  projection = glm::perspective(glm::radians(fov), 800 / 600.0f, 0.1f, 100.0f);
}

void Camera::UpdateCamera() {
  direction.y = sin(glm::radians(pitch));
  direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  cameraFront = glm::normalize(direction);
  view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
  projection = glm::perspective(glm::radians(fov), 800 / 600.0f, 0.1f, 100.0f);
}
#include <iostream>
void Camera::KeyInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    cameraPos += cameraSpeed * cameraFront;

  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    cameraPos -= cameraSpeed * cameraFront;

  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    cameraPos -=
        cameraSpeed * glm::normalize(glm::cross(cameraFront, cameraUp));

  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    cameraPos +=
        cameraSpeed * glm::normalize(glm::cross(cameraFront, cameraUp));
  
  if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) 
    cameraPos += cameraSpeed * cameraUp;

  if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) 
    cameraPos -= cameraSpeed * cameraUp;
  
}

void Camera::InitCallbacks(GLFWwindow *window) {
  glfwSetCursorPosCallback(window, MouseCallback);
  glfwSetScrollCallback(window, ScrollCallback);
}
void Camera::MouseCallback(GLFWwindow *window, double posX, double posY) {
  if (activeCamera->firstMouse) {
    lastX = posX;
    lastY = posY;
    activeCamera->firstMouse = false;
  }
  const float sensitivity = 0.1f;
  auto xOffset = sensitivity * (posX - lastX);
  auto yOffset = sensitivity * (lastY - posY);
  activeCamera->yaw += xOffset;
  activeCamera->pitch += yOffset;
  if (activeCamera->pitch > 89.0f) {
    activeCamera->pitch = 89.0f;
  }
  if (activeCamera->pitch < -89.0f) {
    activeCamera->pitch = -89.0f;
  }

  lastX = posX;
  lastY = posY;
}

void Camera::ScrollCallback(GLFWwindow *window, double _, double yoffset) {
  activeCamera->fov -= (float)yoffset;
  if (activeCamera->fov < 1.0f) {
    activeCamera->fov = 1.0f;
  }
  if (activeCamera->fov > 90.0f) {
    activeCamera->fov = 90.0f;
  }
}