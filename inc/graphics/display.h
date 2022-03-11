#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <chrono>
#include "backend/config.h"
#include "graphics/drawable.h"



namespace NeuronalNet
{
	namespace Graphics
	{
		using std::string;
		using std::vector;
		class NET_API Display
		{
			public:
			Display();
			Display(sf::Vector2u size, const string &title);
			~Display();

			void addDrawable(Drawable* obj);

			

			void frameRateTarget(float fps);
			bool isOpen();
			void loop();
			void processEvents();
			bool needsFrameUpdate();
			void draw();

			

			protected:
			virtual void init(sf::Vector2u size, const string& title);
			

			private:
			sf::RenderWindow* m_window;
			sf::Vector2u m_windowSize;
			string m_windowTitle;

			bool m_exit;
			vector<Drawable*> m_drawableObjList;

			double m_targetFrameTimeMs;
			std::chrono::time_point<std::chrono::high_resolution_clock> *m_frameIntervalTime;
		};
	};
};