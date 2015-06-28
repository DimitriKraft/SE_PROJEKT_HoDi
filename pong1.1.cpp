//////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <stdio.h>



////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////






int main()


{

	
    // Define some constants
    const float pi = 3.14159f;
    sf::Vector2f paddleSize(25, 100);
    float ballRadius = 10.f;
	float ballSpeed = 0;
	float paddleSpeed = 0;
	int singleplayer;
	int gameWidth = 1024;
	int gameHeight = 1024;
	char c=0;
	int x=0;
	int y=0;
	bool isPlaying = false;
	bool isConfig= true;
	bool multipleBalls=false;
	
	///////////////////////////////////////// Console Configuration
	std::cout << "\tHerzlich Willkommen zu unserem Software Engineering Projekt!\n\tVorweg muessen Sie einige Einstellungen treffen.\t\n\n\n";
	
	while (isConfig == true)
	{
		//playmode config
	std::cout << "\Bitte waehlen Sie ihren Spielmodus :\n(1)Einzelspieler oder (2)Mehrspieler (2 Baelle Modus moeglich!)\t\nIhre Auswahl: ";
	std::cin >> c;
	if (c == '1')
	singleplayer = 1;
	if ( c== '2')
	{
		//ballmode config in multiplayermode
	singleplayer = 0;
	std::cout << "\Bitte waehlen Sie wieviele Baelle auf dem Spielfeld erscheinen sollen :\n(1)1 Ball oder (2)2 Baelle\t\nIhre Auswahl: ";
	std::cin >> c;
	if (c == '1')
	multipleBalls=false;
	if ( c== '2')
	multipleBalls=true;
	}
	//random mode if 1 nor 2
	if ( c!= '1' && c!='2')
	{
	srand(time(NULL)); // random number
	singleplayer = rand() % 2;
	std::cout << "Zufaelliger Spielemodus wurde gewaehlt\n";
	std::cout << singleplayer << "\n\n";
	}
	//paddle and ballspeed config
	std::cout << "Bitte waehlen Sie ihre Ballgeschwindigkeit und die Paddlegeschwindigkeit\n(1)langsam oder (2)schnell\nIhre Auswahl:";
	std::cin >> c;
	if(c == '1')
	{
	ballSpeed = 400.f;			
	paddleSpeed = 400.f;
	}
	if(c == '2')
	{
	ballSpeed = 800.f;
	paddleSpeed = 800.f;
	}
	//random paddle and ballspeed if 1 nor 2
	if ( c!= '1' && c!='2')
	{
	ballSpeed = rand() % 800 + 400;			// random ballspeed	
	paddleSpeed = rand() % 800 + 400;		//random paddlespeed
	std::cout << "Zufaellige Geschwindigkeiten wurde gewaehlt\n\n";
	}

	//select gamewidth
	std::cout << "Bitte waehlen Sie ihre Spielfeldbreite in Pixel: ";
	std::cin >> x;
	gameWidth = x;
	//select gameheight
	std::cout << "\nBitte waehlen Sie ihre Spielfeldhoehe in Pixel: ";
	std::cin >> y;
	gameHeight = y;
	//controll settings, if desired - reconfig
	std::cout << "Ihre Einstellungen sind :\nSpielmodus(1 = SP , 0 = MP) = " << singleplayer << "\n2 Bälle Modus =  " << multipleBalls << "\nBallgeschwindigkeit = " << ballSpeed << "\nPaddlegeschwindigkeit = " << paddleSpeed << "\nSpielfeldgroese = " << gameWidth << " * " << gameHeight;   
	std::cout << "\nWollen Sie diese Einstellungen beibehalten? (j/n)";
	std::cin >> c;
	if (c == 'j' || c == 'J')
	{
		isConfig = false;
	}
	if (c == 'n' || c == 'N')
	{
		system("cls");
		isConfig = true;
	}
	}
	
	////////////////////////////////////////////////////////////////////////////////////end Console Configuration
	 
	

	
	
	

    // Create the window of the application
    sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight, 32), "SFML Pong 0.1",
                            sf::Style::Default | sf::Style::Titlebar );
	window.setVerticalSyncEnabled(true);
	
    // Load the sounds used in the game
    sf::SoundBuffer ballSoundBuffer;
    if (!ballSoundBuffer.loadFromFile("ball.wav"))
        return EXIT_FAILURE;
    sf::Sound ballSound(ballSoundBuffer);

    // Create the left paddle
    sf::RectangleShape leftPaddle;
    leftPaddle.setSize(paddleSize - sf::Vector2f(3, 3));
    leftPaddle.setOutlineThickness(3);
    leftPaddle.setOutlineColor(sf::Color::Black);
    leftPaddle.setFillColor(sf::Color(100, 100, 200));
    leftPaddle.setOrigin(paddleSize/ 2.f);

    // Create the right paddle
    sf::RectangleShape rightPaddle;
    rightPaddle.setSize(paddleSize - sf::Vector2f(3, 3));
    rightPaddle.setOutlineThickness(3);
    rightPaddle.setOutlineColor(sf::Color::Black);
    rightPaddle.setFillColor(sf::Color(200, 100, 100));
    rightPaddle.setOrigin(paddleSize / 2.f);
	


    // Create the ball
    sf::CircleShape ball;
    ball.setRadius(ballRadius - 3);
    ball.setOutlineThickness(3);
    ball.setOutlineColor(sf::Color::Black);
    ball.setFillColor(sf::Color::White);
    ball.setOrigin(ballRadius / 2, ballRadius / 2);
	
	// Create the ball
    sf::CircleShape ball2;
    ball2.setRadius(ballRadius - 3);
    ball2.setOutlineThickness(3);
    ball2.setOutlineColor(sf::Color::Black);
    ball2.setFillColor(sf::Color::White);
    ball2.setOrigin(ballRadius / 2, ballRadius / 2);



    // Load the text font
    sf::Font font;
    if (!font.loadFromFile("sansation.ttf"))
        return EXIT_FAILURE;

    // Initialize the pause message
    sf::Text pauseMessage;
    pauseMessage.setFont(font);
    pauseMessage.setCharacterSize(32);
    pauseMessage.setPosition(gameWidth/2, gameHeight/2);
    pauseMessage.setColor(sf::Color::White);
    pauseMessage.setString("Press space to play or escape to exit");




    // Define the paddles properties
    sf::Clock AITimer;
    const sf::Time AITime   = sf::seconds(0.1f);
    float rightPaddleSpeed  = 0.f;
    float ballAngle = 0.f; // to be changed later
	float ballAngle2 = 0.f; // to be changed later
    sf::Clock clock;
    
    while (window.isOpen())
    {
		

			// Handle events
			sf::Event event;
		    while (window.pollEvent(event))

			{
				// Window closed or escape key pressed: exit
				if ((event.type == sf::Event::Closed) ||
				   ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))

					{
					
					window.close();
					break;
					}

				

		

            // Space key pressed: play
				if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space))
				{		
					if (!isPlaying)
					{
                    // (re)start the game
                    isPlaying = true;
				
				



                    clock.restart();

                    // Reset the position of the paddles and ball
                    leftPaddle.setPosition(10 + paddleSize.x / 2, gameHeight / 2);
                    rightPaddle.setPosition(gameWidth - 10 - paddleSize.x / 2, gameHeight / 2);
                    ball.setPosition(gameWidth / 2, gameHeight / 2);
					ball2.setPosition(gameWidth / 3, gameHeight / 3);  //<- new origin position of the second ball 
					
			

                    // Reset the ball angle
                    do
                    {
                        // Make sure the ball initial angle is not too much vertical
                        ballAngle = (std::rand() % 360) * 2 * pi / 360;
						ballAngle2 = (std::rand() % 360) * 2 * pi / 360;  // <-new angle for the second ball
						
						
                    }
                    while (std::abs(std::cos(ballAngle)) < 0.7f);
					
                }
			}
			
		

		}

		

        if (isPlaying == true)
        {
			
            float deltaTime = clock.restart().asSeconds();

            // Move the player 1 's paddle
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
               (leftPaddle.getPosition().y - paddleSize.y / 2 > 5.f))
            {
                leftPaddle.move(0.f, -paddleSpeed * deltaTime);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
               (leftPaddle.getPosition().y + paddleSize.y / 2 < gameHeight - 5.f))
            {
                leftPaddle.move(0.f, paddleSpeed * deltaTime);
            }
			  // NEW Move the player 2 's paddle (copy of the original and replaced the keys and added conditions)
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && 
               (rightPaddle.getPosition().y - paddleSize.y / 2 > 5.f) && singleplayer == 0) 
            {
                rightPaddle.move(0.f, -paddleSpeed * deltaTime);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
               (rightPaddle.getPosition().y + paddleSize.y / 2 < gameHeight - 5.f) && singleplayer == 0)
            {
                rightPaddle.move(0.f, paddleSpeed * deltaTime);
            }



			
			
			// Move the computer's paddle
            if (singleplayer == 1 && ((rightPaddleSpeed < 0.f) && (rightPaddle.getPosition().y - paddleSize.y / 2 > 5.f)) ||
                ((rightPaddleSpeed > 0.f) && (rightPaddle.getPosition().y + paddleSize.y / 2 < gameHeight - 5.f)))
            {
                rightPaddle.move(0.f, rightPaddleSpeed * deltaTime);
            }

		

			// Move the ball
            float factor = ballSpeed * deltaTime;
            ball.move(std::cos(ballAngle) * factor, std::sin(ballAngle) * factor);
			// NEW Move the second ball
			if (singleplayer == false && multipleBalls == true) // NEW condition for the activation of the second ball
			{
			float factor2 = ballSpeed * deltaTime;
            ball2.move(std::cos(ballAngle2) * factor, std::sin(ballAngle2) * factor2); //<- NEW defines the movement of the second ball
			}
			
			// Update the computer's paddle direction according to the ball position
            if (AITimer.getElapsedTime() > AITime && singleplayer == 1)
            {
                AITimer.restart();
                if (ball.getPosition().y + ballRadius > rightPaddle.getPosition().y + paddleSize.y / 2)
                    rightPaddleSpeed = paddleSpeed;
                else if (ball.getPosition().y - ballRadius < rightPaddle.getPosition().y - paddleSize.y / 2)
                    rightPaddleSpeed = -paddleSpeed;
                else
                    rightPaddleSpeed = 0.f;
            }

			// Check collisions between the ball and the screen Ball 1
            if (ball.getPosition().x - ballRadius < 0.f)
            {
                isPlaying = false;
                pauseMessage.setString("You lost!\nPress space to restart or\nescape to exit");
            }
            if (ball.getPosition().x + ballRadius > gameWidth)
            {
                isPlaying = false;
                pauseMessage.setString("You won!\nPress space to restart or\nescape to exit");
            }
            if (ball.getPosition().y - ballRadius < 0.f)
            {
                ballSound.play();
                ballAngle = -ballAngle;
                ball.setPosition(ball.getPosition().x, ballRadius + 0.1f);
				
            }
            if (ball.getPosition().y + ballRadius > gameHeight)
            {
                ballSound.play();
                ballAngle = -ballAngle;
                ball.setPosition(ball.getPosition().x, gameHeight - ballRadius - 0.1f);
				
            }


			// NEW Check collisions between the ball and the screen Ball 2  (copy of the original code and replaced ball. with ball2. object and ballAngle with ballAngle 2)
            if (ball2.getPosition().x - ballRadius < 0.f)
            {
                isPlaying = false;
                pauseMessage.setString("You lost!\nPress space to restart or\nescape to exit");
            }
            if (ball2.getPosition().x + ballRadius > gameWidth)
            {
                isPlaying = false;
                pauseMessage.setString("You won!\nPress space to restart or\nescape to exit");
            }
            if (ball2.getPosition().y - ballRadius < 0.f)
            {
                ballSound.play();
                ballAngle2 = -ballAngle2;
                ball2.setPosition(ball2.getPosition().x, ballRadius + 0.1f);
				
            }
            if (ball2.getPosition().y + ballRadius > gameHeight)
            {
                ballSound.play();
                ballAngle2 = -ballAngle2;
                ball2.setPosition(ball2.getPosition().x, gameHeight - ballRadius - 0.1f);
				
            }





			// Check the collisions between the balls and the paddles
            // Left Paddle Ball 1
            if (ball.getPosition().x - ballRadius < leftPaddle.getPosition().x + paddleSize.x / 2 &&
                ball.getPosition().x - ballRadius > leftPaddle.getPosition().x &&
                ball.getPosition().y + ballRadius >= leftPaddle.getPosition().y - paddleSize.y / 2 &&
                ball.getPosition().y - ballRadius <= leftPaddle.getPosition().y + paddleSize.y / 2)
            {
                if (ball.getPosition().y > leftPaddle.getPosition().y)
                    ballAngle = pi - ballAngle + (std::rand() % 20) * pi / 180;
                else
                    ballAngle = pi - ballAngle - (std::rand() % 20) * pi / 180;

                ballSound.play();
                ball.setPosition(leftPaddle.getPosition().x + ballRadius + paddleSize.x / 2 + 0.1f, ball.getPosition().y);
            }


			  // NEW Left Paddle Ball 2 (copy of the original code and replaced ball. with ball2. object and ballAngle with ballAngle 2)
            if (ball2.getPosition().x - ballRadius < leftPaddle.getPosition().x + paddleSize.x / 2 &&
                ball2.getPosition().x - ballRadius > leftPaddle.getPosition().x &&
                ball2.getPosition().y + ballRadius >= leftPaddle.getPosition().y - paddleSize.y / 2 &&
                ball2.getPosition().y - ballRadius <= leftPaddle.getPosition().y + paddleSize.y / 2)
            {
                if (ball2.getPosition().y > leftPaddle.getPosition().y)
                    ballAngle2 = pi - ballAngle2 + (std::rand() % 20) * pi / 180;
                else
                    ballAngle2 = pi - ballAngle2 - (std::rand() % 20) * pi / 180;

                ballSound.play();
                ball2.setPosition(leftPaddle.getPosition().x + ballRadius + paddleSize.x / 2 + 0.1f, ball2.getPosition().y);
            }

            // Right Paddle
            if (ball.getPosition().x + ballRadius > rightPaddle.getPosition().x - paddleSize.x / 2 &&
                ball.getPosition().x + ballRadius < rightPaddle.getPosition().x &&
                ball.getPosition().y + ballRadius >= rightPaddle.getPosition().y - paddleSize.y / 2 &&
                ball.getPosition().y - ballRadius <= rightPaddle.getPosition().y + paddleSize.y / 2)
            {
                if (ball.getPosition().y > rightPaddle.getPosition().y)
                    ballAngle = pi - ballAngle + (std::rand() % 20) * pi / 180;
                else
                    ballAngle = pi - ballAngle - (std::rand() % 20) * pi / 180;

                ballSound.play();
                ball.setPosition(rightPaddle.getPosition().x - ballRadius - paddleSize.x / 2 - 0.1f, ball.getPosition().y);
            }
         // NEW Right Paddle Ball 2 (copy of the original code and replaced ball. with ball2. object and ballAngle with ballAngle 2)
            if (ball2.getPosition().x + ballRadius > rightPaddle.getPosition().x - paddleSize.x / 2 &&
                ball2.getPosition().x + ballRadius < rightPaddle.getPosition().x &&
                ball2.getPosition().y + ballRadius >= rightPaddle.getPosition().y - paddleSize.y / 2 &&
                ball2.getPosition().y - ballRadius <= rightPaddle.getPosition().y + paddleSize.y / 2)
            {
                if (ball2.getPosition().y > rightPaddle.getPosition().y)
                    ballAngle2 = pi - ballAngle2 + (std::rand() % 20) * pi / 180;
                else
                    ballAngle2 = pi - ballAngle2 - (std::rand() % 20) * pi / 180;

                ballSound.play();
                ball2.setPosition(rightPaddle.getPosition().x - ballRadius - paddleSize.x / 2 - 0.1f, ball2.getPosition().y);
            }
		

		}



        // Clear the window
        window.clear(sf::Color(100, 200, 50));

        if (isPlaying)
        {
            // Draw the paddles and the ball
            window.draw(leftPaddle);
            window.draw(rightPaddle);
            window.draw(ball);
			if (multipleBalls == true) // NEW condition to draw a second ball
			window.draw(ball2);
        }
        else
        {
            // Draw the pause message
            window.draw(pauseMessage);
			
        }

        // Display things on screen
        window.display();
    }
	
	
	return EXIT_SUCCESS;
	}
	
