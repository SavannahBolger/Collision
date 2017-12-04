/// <summary>
/// Practical 4
/// @author: Savannah Bolger
/// @student no: C00215747
/// @date 3/12/2017
/// </summary>

/*#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif */

#ifndef _DEBUG
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif // !_DEBUG


#include <iostream>
#include "SFML\Graphics.hpp"
#define TINYC2_IMPL
#include "tinyc2.h"

int main()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Practical 4");

	int player = 1;
	std::cout << "Default player = AABB/nPress 1 for AABB player/nPress 2 for Circle player/nPress 3 for Ray player";
	sf::RectangleShape aabb;
	sf::Vector2f aabbSize(100, 100);
	aabb.setSize(aabbSize);
	sf::Vector2f aabbPos(0, 0);
	aabb.setPosition(aabbPos);
	c2AABB m_npcAABB;
	m_npcAABB.min = c2V(aabb.getPosition().x, aabb.getPosition().y);
	m_npcAABB.max = c2V(aabb.getPosition().x + aabb.getSize().x, aabb.getPosition().y + aabb.getSize().y);

	sf::CircleShape circleCap1(60.0f);
	circleCap1.setPosition(400, 10);
	sf::CircleShape circleCap2(60.0f);
	circleCap2.setPosition(520, 10);
	sf::RectangleShape rectCap;
	sf::Vector2f capsuleSize(120, 120);
	rectCap.setSize(capsuleSize);
	sf::Vector2f capsulePos(460, 10);
	rectCap.setPosition(capsulePos);
	c2Capsule m_npcCapsule;
	m_npcCapsule.a = c2V(circleCap1.getPosition().x + circleCap1.getRadius(), circleCap1.getPosition().y + circleCap1.getRadius());
	m_npcCapsule.b = c2V(circleCap2.getPosition().x + circleCap2.getRadius(), circleCap2.getPosition().y + circleCap2.getRadius());
	m_npcCapsule.r = 120;

	sf::VertexArray ray{ sf::Lines };
	sf::Vertex start;
	sf::Vertex end;
	sf::Vector2f startpoint(400.0f, 430.0f);
	sf::Vector2f endpoint(500.0f, 430.0f);
	sf::Color rayColour = sf::Color(0, 255, 0);
	start = sf::Vertex(static_cast<sf::Vector2f>(startpoint), rayColour);
	end = sf::Vertex(static_cast<sf::Vector2f>(endpoint), rayColour);
	ray.append(start);
	ray.append(end);
	c2Ray m_npcRay;
	m_npcRay.d = c2V(startpoint.x - endpoint.x, startpoint.y - endpoint.y);
	m_npcRay.t = startpoint.x - endpoint.x;
	m_npcRay.p = c2V(startpoint.x, startpoint.y);

	sf::Color polyColor;
	polyColor = sf::Color(0, 255, 0);
	sf::VertexArray quad{ sf::Quads };
	sf::Vertex vertex[4] = { { { 50,200 },polyColor },{ { 150,200 },polyColor },{ { 250,300 },polyColor },{ { 150,300 },polyColor } };
	c2Poly m_npcPolygon;
	m_npcPolygon.count = 4;
	m_npcPolygon.verts[0] = c2V(50, 200);
	m_npcPolygon.verts[1] = c2V(150, 200);
	m_npcPolygon.verts[2] = c2V(250, 300);
	m_npcPolygon.verts[3] = c2V(150, 300);

	sf::CircleShape circle(15.0f);
	circle.setPosition(400, 300);
	c2Circle m_npcCircle;
	m_npcCircle.p = c2V(circle.getPosition().x, circle.getPosition().y);
	m_npcCircle.r = 30.0f;

	c2AABB m_playerAABB;
	sf::RectangleShape m_playerAABBShape;
	sf::Vector2f playerAABBSize(100, 100);
	m_playerAABBShape.setSize(playerAABBSize);
	m_playerAABBShape.setFillColor(sf::Color::Cyan);

	c2Circle m_playerCircle;
	sf::CircleShape m_playerCircleShape(60.0f);
	m_playerCircleShape.setPosition(400, 10);
	m_playerCircleShape.setFillColor(sf::Color::Cyan);

	c2Ray m_playerRay;
	sf::VertexArray playerRay{ sf::Lines };
	sf::Vertex playerStart;
	sf::Vertex playerEnd;
	

	while (window.isOpen())
	{
		for (size_t index = 0; index < 4; index++)
		{
			quad.append(vertex[index]);
		}
		// Move Sprite Follow Mouse
		m_playerAABBShape.setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
		m_playerCircleShape.setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));

		// Update mouse AABB
		m_playerAABB.min = c2V(m_playerAABBShape.getPosition().x, m_playerAABBShape.getPosition().y);
		m_playerAABB.max = c2V(m_playerAABBShape.getPosition().x + m_playerAABBShape.getGlobalBounds().width, m_playerAABBShape.getPosition().y + m_playerAABBShape.getGlobalBounds().width);
		
		// Update mouse Circle
		m_playerCircle.p = c2V(m_playerCircleShape.getPosition().x, m_playerCircleShape.getPosition().y);
		m_playerCircle.r = 120.0f;

		// Update mouse Ray
		sf::Vector2f playerStartpoint(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
		sf::Vector2f playerEndpoint(playerStartpoint.x + 100, playerStartpoint.y);
		playerStart = sf::Vertex(static_cast<sf::Vector2f>(playerStartpoint), sf::Color::Cyan);
		playerEnd = sf::Vertex(static_cast<sf::Vector2f>(playerEndpoint), sf::Color::Cyan);
		playerRay.append(playerStart);
		playerRay.append(playerEnd);
		m_playerRay.d = c2V(playerStartpoint.x - endpoint.x, startpoint.y - endpoint.y);
		m_playerRay.t = playerStartpoint.x - endpoint.x;
		m_playerRay.p = c2V(playerStartpoint.x, startpoint.y);

		// Collision result
		int result = 0;

		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
			{
				player = 1;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
			{
				player = 2;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
			{
				player = 3;
			}
		}

		// Check for collisions
		if (player == 1)
		{
			if (aabb.getGlobalBounds().intersects(m_playerAABBShape.getGlobalBounds()))
			{
				result = c2AABBtoAABB(m_npcAABB, m_playerAABB);
			}
			if (circle.getGlobalBounds().intersects(m_playerAABBShape.getGlobalBounds()))
			{
				result = c2CircletoAABB(m_npcCircle, m_playerAABB);
			}
			if (quad.getBounds().intersects(m_playerAABBShape.getGlobalBounds()))
			{
				result = c2AABBtoPoly(m_playerAABB, &m_npcPolygon, NULL);
			}
			if (ray.getBounds().intersects(m_playerAABBShape.getGlobalBounds()))
			{
				//result = c2RaytoAABB(m_npcRay, m_playerAABB, );
			}

			if (circleCap1.getGlobalBounds().intersects(m_playerAABBShape.getGlobalBounds()))
			{
				result = c2AABBtoCapsule(m_playerAABB, m_npcCapsule);
			}
			else if (circleCap2.getGlobalBounds().intersects(m_playerAABBShape.getGlobalBounds()))
			{
				result = c2AABBtoCapsule(m_playerAABB, m_npcCapsule);
			}
		}
		if (player == 2)
		{
			if (aabb.getGlobalBounds().intersects(m_playerCircleShape.getGlobalBounds()))
			{
				result = c2CircletoAABB(m_playerCircle, m_npcAABB);
			}
			if (circle.getGlobalBounds().intersects(m_playerCircleShape.getGlobalBounds()))
			{
				result = c2CircletoCircle(m_npcCircle, m_playerCircle);
			}
			if (quad.getBounds().intersects(m_playerCircleShape.getGlobalBounds()))
			{
				result = c2CircletoPoly(m_playerCircle, &m_npcPolygon, NULL);
			}
			if (ray.getBounds().intersects(m_playerCircleShape.getGlobalBounds()))
			{
				//result = c2RaytoCircle(m_npcRay, m_playerCircle,);
			}

			if (circleCap1.getGlobalBounds().intersects(m_playerCircleShape.getGlobalBounds()))
			{
				result = c2CircletoCapsule(m_playerCircle, m_npcCapsule);
			}
			else if (circleCap2.getGlobalBounds().intersects(m_playerCircleShape.getGlobalBounds()))
			{
				result = c2CircletoCapsule(m_playerCircle, m_npcCapsule);
			}
		}
		if (player == 3)
		{
			if (aabb.getGlobalBounds().intersects(playerRay.getBounds()))
			{
				//result = c2RaytoAABB(m_playerRay, m_npcAABB);
			}
			if (circle.getGlobalBounds().intersects(playerRay.getBounds()))
			{
				//result = c2RaytoCircle(m_playerRay, m_npcCircle);
			}
			if (quad.getBounds().intersects(playerRay.getBounds()))
			{
				//result = c2RaytoPoly(m_playerRay, &m_npcPolygon, NULL);
			}

			if (circleCap1.getGlobalBounds().intersects(playerRay.getBounds()))
			{
				//result = c2RaytoCapsule(m_playerRay, m_npcCapsule);
			}
			else if (circleCap2.getGlobalBounds().intersects(playerRay.getBounds()))
			{
				//result = c2RaytoCapsule(m_playerRay, m_npcCapsule);
			}
		}


		std::cout << ((result != 0) ? ("Collision") : "") << std::endl;
		if (result) 
		{
			if (player == 1)
			{
				if (aabb.getGlobalBounds().intersects(m_playerAABBShape.getGlobalBounds()))
				{
					aabb.setFillColor(sf::Color(255, 0, 0));
				}
				if (circle.getGlobalBounds().intersects(m_playerAABBShape.getGlobalBounds()))
				{
					circle.setFillColor(sf::Color(255, 0, 0));
				}
				if (quad.getBounds().intersects(m_playerAABBShape.getGlobalBounds()))
				{
					polyColor = sf::Color(255, 0, 0);
					vertex[0] = { { 50,200 },polyColor };
					vertex[1] = { { 150, 200 }, polyColor };
					vertex[2] = { { 250,300 },polyColor }; 
					vertex[3] = { { 150, 300 }, polyColor };
				
				}
				if (ray.getBounds().intersects(m_playerAABBShape.getGlobalBounds()))
				{
					rayColour = sf::Color(255, 0, 0);
				}

				if (circleCap1.getGlobalBounds().intersects(m_playerAABBShape.getGlobalBounds()))
				{
					circleCap1.setFillColor(sf::Color(255, 0, 0));
					circleCap2.setFillColor(sf::Color(255, 0, 0));
					rectCap.setFillColor(sf::Color(255, 0, 0));
				}
				else if (circleCap2.getGlobalBounds().intersects(m_playerAABBShape.getGlobalBounds()))
				{
					circleCap1.setFillColor(sf::Color(255, 0, 0));
					circleCap2.setFillColor(sf::Color(255, 0, 0));
					rectCap.setFillColor(sf::Color(255, 0, 0));
				}
			}
			if (player == 2)
			{
				if (aabb.getGlobalBounds().intersects(m_playerCircleShape.getGlobalBounds()))
				{
					aabb.setFillColor(sf::Color(255, 0, 0));
				}
				if (circle.getGlobalBounds().intersects(m_playerCircleShape.getGlobalBounds()))
				{
					circle.setFillColor(sf::Color(255, 0, 0));
				}
				if (quad.getBounds().intersects(m_playerCircleShape.getGlobalBounds()))
				{
					polyColor = sf::Color(255, 0, 0);
					vertex[0] = { { 50,200 },polyColor };
					vertex[1] = { { 150, 200 }, polyColor };
					vertex[2] = { { 250,300 },polyColor };
					vertex[3] = { { 150, 300 }, polyColor };
				}
				if (ray.getBounds().intersects(m_playerCircleShape.getGlobalBounds()))
				{
					rayColour = sf::Color(255, 0, 0);
				}

				if (circleCap1.getGlobalBounds().intersects(m_playerCircleShape.getGlobalBounds()))
				{
					circleCap1.setFillColor(sf::Color(255, 0, 0));
					circleCap2.setFillColor(sf::Color(255, 0, 0));
					rectCap.setFillColor(sf::Color(255, 0, 0));
				}
				else if (circleCap2.getGlobalBounds().intersects(m_playerCircleShape.getGlobalBounds()))
				{
					circleCap1.setFillColor(sf::Color(255, 0, 0));
					circleCap2.setFillColor(sf::Color(255, 0, 0));
					rectCap.setFillColor(sf::Color(255, 0, 0));
				}
			}
			if (player == 3)
			{
				if (aabb.getGlobalBounds().intersects(playerRay.getBounds()))
				{
					aabb.setFillColor(sf::Color(255, 0, 0));
				}
				if (circle.getGlobalBounds().intersects(playerRay.getBounds()))
				{
					circle.setFillColor(sf::Color(255, 0, 0));
				}
				if (quad.getBounds().intersects(playerRay.getBounds()))
				{
					polyColor = sf::Color(255, 0, 0);
					vertex[0] = { { 50,200 },polyColor };
					vertex[1] = { { 150, 200 }, polyColor };
					vertex[2] = { { 250,300 },polyColor };
					vertex[3] = { { 150, 300 }, polyColor };
				}
				

				if (circleCap1.getGlobalBounds().intersects(playerRay.getBounds()))
				{
					circleCap1.setFillColor(sf::Color(255, 0, 0));
					circleCap2.setFillColor(sf::Color(255, 0, 0));
					rectCap.setFillColor(sf::Color(255, 0, 0));
				}
				else if (circleCap2.getGlobalBounds().intersects(playerRay.getBounds()))
				{
					circleCap1.setFillColor(sf::Color(255, 0, 0));
					circleCap2.setFillColor(sf::Color(255, 0, 0));
					rectCap.setFillColor(sf::Color(255, 0, 0));
				}
			}
		}
		else 
		{
			if (player == 1)
			{

				if (!(aabb.getGlobalBounds().intersects(m_playerAABBShape.getGlobalBounds())))
				{
					aabb.setFillColor(sf::Color(0, 255, 0));
				}
				if (!(circle.getGlobalBounds().intersects(m_playerAABBShape.getGlobalBounds())))
				{
					circle.setFillColor(sf::Color(0, 255, 0));
				}
				if (!(quad.getBounds().intersects(m_playerAABBShape.getGlobalBounds())))
				{
					polyColor = sf::Color(0, 255, 0);
					vertex[0] = { { 50,200 },polyColor };
					vertex[1] = { { 150, 200 }, polyColor };
					vertex[2] = { { 250,300 },polyColor };
					vertex[3] = { { 150, 300 }, polyColor };
				}
				if (!(ray.getBounds().intersects(m_playerAABBShape.getGlobalBounds())))
				{
					rayColour = sf::Color(0, 255, 0);
				}

				if (!(circleCap1.getGlobalBounds().intersects(m_playerAABBShape.getGlobalBounds())))
				{
					circleCap1.setFillColor(sf::Color(0, 255, 0));
					circleCap2.setFillColor(sf::Color(0, 255, 0));
					rectCap.setFillColor(sf::Color(0, 255, 0));
				}
				else if (!(circleCap2.getGlobalBounds().intersects(m_playerAABBShape.getGlobalBounds())))
				{
					circleCap1.setFillColor(sf::Color(0, 255, 0));
					circleCap2.setFillColor(sf::Color(0, 255, 0));
					rectCap.setFillColor(sf::Color(0, 255, 0));
				}
			}
			if (player == 2)
			{
				if (!(aabb.getGlobalBounds().intersects(m_playerCircleShape.getGlobalBounds())))
				{
					aabb.setFillColor(sf::Color(0, 255, 0));
				}
				if (!(circle.getGlobalBounds().intersects(m_playerCircleShape.getGlobalBounds())))
				{
					circle.setFillColor(sf::Color(0, 255, 0));
				}
				if (!(quad.getBounds().intersects(m_playerCircleShape.getGlobalBounds())))
				{
					polyColor = sf::Color(0, 255, 0);
					vertex[0] = { { 50,200 },polyColor };
					vertex[1] = { { 150, 200 }, polyColor };
					vertex[2] = { { 250,300 },polyColor };
					vertex[3] = { { 150, 300 }, polyColor };
				}
				if (!(ray.getBounds().intersects(m_playerCircleShape.getGlobalBounds())))
				{
					rayColour = sf::Color(0, 255, 0);
				}

				if (!(circleCap1.getGlobalBounds().intersects(m_playerCircleShape.getGlobalBounds())))
				{
					circleCap1.setFillColor(sf::Color(0, 255, 0));
					circleCap2.setFillColor(sf::Color(0, 255, 0));
					rectCap.setFillColor(sf::Color(0, 255, 0));
				}
				else if (!(circleCap2.getGlobalBounds().intersects(m_playerCircleShape.getGlobalBounds())))
				{
					circleCap1.setFillColor(sf::Color(0, 255, 0));
					circleCap2.setFillColor(sf::Color(0, 255, 0));
					rectCap.setFillColor(sf::Color(0, 255, 0));
				}
			}
			if (player == 3)
			{
				if (!(aabb.getGlobalBounds().intersects(playerRay.getBounds())))
				{
					aabb.setFillColor(sf::Color(0, 255, 0));
				}
				if (!(circle.getGlobalBounds().intersects(playerRay.getBounds())))
				{
					circle.setFillColor(sf::Color(0, 255, 0));
				}
				if (!(quad.getBounds().intersects(playerRay.getBounds())))
				{
					polyColor = sf::Color(0, 255, 0);
					vertex[0] = { { 50,200 },polyColor };
					vertex[1] = { { 150, 200 }, polyColor };
					vertex[2] = { { 250,300 },polyColor };
					vertex[3] = { { 150, 300 }, polyColor };
				}
				

				if (!(circleCap1.getGlobalBounds().intersects(playerRay.getBounds())))
				{
					circleCap1.setFillColor(sf::Color(0, 255, 0));
					circleCap2.setFillColor(sf::Color(0, 255, 0));
					rectCap.setFillColor(sf::Color(0, 255, 0));
				}
				else if (!(circleCap2.getGlobalBounds().intersects(playerRay.getBounds())))
				{
					circleCap1.setFillColor(sf::Color(0, 255, 0));
					circleCap2.setFillColor(sf::Color(0, 255, 0));
					rectCap.setFillColor(sf::Color(0, 255, 0));
				}
			}
		}

		// Clear screen
		window.clear();

		// Draw the Players Current Animated Sprite
		window.draw(aabb);
		window.draw(circle);
		window.draw(quad);
		window.draw(circleCap1);
		window.draw(circleCap2);
		window.draw(rectCap);
		window.draw(ray);

		if (player == 1)
		{
			window.draw(m_playerAABBShape);
		}
		if (player == 2)
		{
			window.draw(m_playerCircleShape);
		}
		if (player == 3)
		{
			window.draw(playerRay);
		}
		// Update the window
		window.display();
	}
}