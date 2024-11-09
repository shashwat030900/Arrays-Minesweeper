#pragma once
#include "../../header/UI/Interface/IUIController.h"
#include "../../header/UI/UIElement/ImageView.h"
#include "../../header/UI/UIElement/ButtonView.h"
#include "../../header/UI/UIElement/TextView.h"

namespace UI
{
	namespace Instructions
	{
		class InstructionsScreenUIController : public Interface::IUIController
		{
		private:
			// Constants:
			const float button_width = 400.f;
			const float button_height = 140.f;

			const float menu_button_y_position = 800.f;
			const float background_alpha = 85.f;

			static const int number_of_instructions = 7;
			const float top_offset = 97.f;
			const float text_spacing = 95.f;
			const int font_size = 50;

			const sf::Color text_color = sf::Color::White;

			sf::String instructions[number_of_instructions] = { "The 'Mines' are hidden in a grid of cells",
																"'Number' cell tell's you, how many 'Mines' are adjacent to that cell",
																"You can use the number 'Clues' to solve the game by opening all of the safe cells",
																"If you click on a 'Mine' you 'Lose' the game!",
																"Open squares with the 'Left Mouse Button' and put 'Flags' with the 'Right Mouse Button'",
																"If you open a 'Empty' square, the adjacent 'Empty' squares will automatically open",
																"A counter shows the number of 'Mines' and a 'Clock' shows your time in seconds." };

			UIElement::ImageView* background_image;
			UIElement::ButtonView* menu_button;

			std::vector<UIElement::TextView*> instructions_text_list;

			void createImage();
			void createButtons();
			void createText();
			void initializeBackgroundImage();
			void initializeButtons();
			void initializeTexts();
			void registerButtonCallback();

			void menuButtonCallback();

			void destroy();

		public:
			InstructionsScreenUIController();
			~InstructionsScreenUIController();

			void initialize() override;
			void update() override;
			void render() override;
			void show() override;
		};
	}
}