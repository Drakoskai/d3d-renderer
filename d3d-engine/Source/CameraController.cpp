#include "pch.h"
#include "CameraController.h"
#include "DXMath.h"

CameraController::CameraController() :
	m_positionX(0.0f),
	m_positionY(0.0f),
	m_positionZ(0.0f),
	m_rotationX(0.0f),
	m_rotationY(0.0f),
	m_rotationZ(0.0f),
	m_frameTime(0.0f),
	m_forwardSpeed(0.0f),
	m_backwardSpeed(0.0f),
	m_upwardSpeed(0.0f),
	m_downwardSpeed(0.0f),
	m_leftTurnSpeed(0.0f),
	m_rightTurnSpeed(0.0f),
	m_lookUpSpeed(0.0f),
	m_lookDownSpeed(0.0f) {}

CameraController::CameraController(const CameraController&) :
	m_positionX(0.0f),
	m_positionY(0.0f),
	m_positionZ(0.0f),
	m_rotationX(0.0f),
	m_rotationY(0.0f),
	m_rotationZ(0.0f),
	m_frameTime(0.0f),
	m_forwardSpeed(0.0f),
	m_backwardSpeed(0.0f),
	m_upwardSpeed(0.0f),
	m_downwardSpeed(0.0f),
	m_leftTurnSpeed(0.0f),
	m_rightTurnSpeed(0.0f),
	m_lookUpSpeed(0.0f),
	m_lookDownSpeed(0.0f) {}

CameraController::~CameraController() {}

void CameraController::SetPosition(float x, float y, float z) {
	m_positionX = x;
	m_positionY = y;
	m_positionZ = z;;
}

void CameraController::SetRotation(float x, float y, float z) {
	m_rotationX = x;
	m_rotationY = y;
	m_rotationZ = z;
}

void CameraController::GetPosition(float& x, float& y, float& z) const {
	x = m_positionX;
	y = m_positionY;
	z = m_positionZ;
}

Vector3 CameraController::GetPosition() const {
	return Vector3(m_positionX, m_positionY, m_positionZ);
}

void CameraController::GetRotation(float& x, float& y, float& z) const {
	x = m_rotationX;
	y = m_rotationY;
	z = m_rotationZ;
}

Vector3 CameraController::GetRotation() const {
	return Vector3(m_rotationX, m_rotationY, m_rotationZ);
}

void CameraController::SetFrameTime(float time) {
	m_frameTime = time;
}

void CameraController::KeyPressed(KeyEvent e) {
	MoveForward(e.wKey);
	MoveBackward(e.sKey);
	TurnLeft(e.aKey);
	TurnRight(e.dKey);
}

void CameraController::MoveForward(bool keydown) {
	// Update the forward speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown) {
		m_forwardSpeed += m_frameTime * 1.0f;
		if (m_forwardSpeed > (m_frameTime * 50.0f)) {
			m_forwardSpeed = m_frameTime * 50.0f;
		}
	} else {
		m_forwardSpeed -= m_frameTime * 0.5f;

		if (m_forwardSpeed < 0.0f) {
			m_forwardSpeed = 0.0f;
		}
	}

	// Convert degrees to radians.
	float radians = m_rotationY * 0.0174532925f;

	// Update the position.
	m_positionX += sinf(radians) * m_forwardSpeed;
	m_positionZ += cosf(radians) * m_forwardSpeed;
}

void CameraController::MoveBackward(bool keydown) {
	// Update the backward speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown) {
		m_backwardSpeed += m_frameTime * 1.0f;

		if (m_backwardSpeed > (m_frameTime * 50.0f)) {
			m_backwardSpeed = m_frameTime * 50.0f;
		}
	} else {
		m_backwardSpeed -= m_frameTime * 0.5f;

		if (m_backwardSpeed < 0.0f) {
			m_backwardSpeed = 0.0f;
		}
	}

	// Convert degrees to radians.
	float radians = m_rotationY * 0.0174532925f;

	// Update the position.
	m_positionX -= sinf(radians) * m_backwardSpeed;
	m_positionZ -= cosf(radians) * m_backwardSpeed;
}

void CameraController::MoveUpward(bool keydown) {
	// Update the upward speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown) {
		m_upwardSpeed += m_frameTime * 1.5f;

		if (m_upwardSpeed > (m_frameTime * 15.0f)) {
			m_upwardSpeed = m_frameTime * 15.0f;
		}
	} else {
		m_upwardSpeed -= m_frameTime * 0.5f;

		if (m_upwardSpeed < 0.0f) {
			m_upwardSpeed = 0.0f;
		}
	}

	// Update the height position.
	m_positionY += m_upwardSpeed;
}

void CameraController::MoveDownward(bool keydown) {
	// Update the downward speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown) {
		m_downwardSpeed += m_frameTime * 1.5f;

		if (m_downwardSpeed > (m_frameTime * 15.0f)) {
			m_downwardSpeed = m_frameTime * 15.0f;
		}
	} else {
		m_downwardSpeed -= m_frameTime * 0.5f;

		if (m_downwardSpeed < 0.0f) {
			m_downwardSpeed = 0.0f;
		}
	}

	// Update the height position.
	m_positionY -= m_downwardSpeed;
}

void CameraController::TurnLeft(bool keydown) {
	// Update the left turn speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown) {
		m_leftTurnSpeed += m_frameTime * 5.0f;

		if (m_leftTurnSpeed > (m_frameTime * 150.0f)) {
			m_leftTurnSpeed = m_frameTime * 150.0f;
		}
	} else {
		m_leftTurnSpeed -= m_frameTime* 3.5f;

		if (m_leftTurnSpeed < 0.0f) {
			m_leftTurnSpeed = 0.0f;
		}
	}

	// Update the rotation.
	m_rotationY -= m_leftTurnSpeed;

	// Keep the rotation in the 0 to 360 range.
	if (m_rotationY < 0.0f) {
		m_rotationY += 360.0f;
	}
}

void CameraController::TurnRight(bool keydown) {
	// Update the right turn speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown) {
		m_rightTurnSpeed += m_frameTime * 5.0f;

		if (m_rightTurnSpeed > (m_frameTime * 150.0f)) {
			m_rightTurnSpeed = m_frameTime * 150.0f;
		}
	} else {
		m_rightTurnSpeed -= m_frameTime* 3.5f;

		if (m_rightTurnSpeed < 0.0f) {
			m_rightTurnSpeed = 0.0f;
		}
	}

	// Update the rotation.
	m_rotationY += m_rightTurnSpeed;

	// Keep the rotation in the 0 to 360 range.
	if (m_rotationY > 360.0f) {
		m_rotationY -= 360.0f;
	}
}

void CameraController::LookUpward(bool keydown) {
	// Update the upward rotation speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown) {
		m_lookUpSpeed += m_frameTime * 7.5f;

		if (m_lookUpSpeed > (m_frameTime * 75.0f)) {
			m_lookUpSpeed = m_frameTime * 75.0f;
		}
	} else {
		m_lookUpSpeed -= m_frameTime* 2.0f;

		if (m_lookUpSpeed < 0.0f) {
			m_lookUpSpeed = 0.0f;
		}
	}

	// Update the rotation.
	m_rotationX -= m_lookUpSpeed;

	// Keep the rotation maximum 90 degrees.
	if (m_rotationX > 90.0f) {
		m_rotationX = 90.0f;
	}
}

void CameraController::LookDownward(bool keydown) {
	// Update the downward rotation speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown) {
		m_lookDownSpeed += m_frameTime * 7.5f;

		if (m_lookDownSpeed > (m_frameTime * 75.0f)) {
			m_lookDownSpeed = m_frameTime * 75.0f;
		}
	} else {
		m_lookDownSpeed -= m_frameTime* 2.0f;

		if (m_lookDownSpeed < 0.0f) {
			m_lookDownSpeed = 0.0f;
		}
	}

	// Update the rotation.
	m_rotationX += m_lookDownSpeed;

	// Keep the rotation maximum 90 degrees.
	if (m_rotationX < -90.0f) {
		m_rotationX = -90.0f;
	}
}
