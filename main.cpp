#include <windows.h>
#include <iostream>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <main.hpp>
#include <node.hpp>
#include <pathfinder.hpp>

/**
 * 
 */
int main()
{
    PathFinder pf = PathFinder(51, 51);
    pf.setTarget(47, 25); //Set target first as we need it to calculate the heuristic distance for the start
    pf.setStart(3, 25);

    int draw_origin_offset = 50;
    int field_padding = 3;
    int field_size = 15;
    bool ctrl_key_state = false;
    bool shift_key_state = false;
    bool success = false;
    bool running = false;
    
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "My window");
    std::vector<std::vector<Node>> field;

    while(window.isOpen()){
        sf::Event event;
        while( window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            } else if(event.type == sf::Event::MouseButtonPressed){
                if(event.mouseButton.button == sf::Mouse::Left){
                    int new_x = (event.mouseButton.x-draw_origin_offset)/(field_size+field_padding);
                    int new_y = (event.mouseButton.y-draw_origin_offset)/(field_size+field_padding);
                    std::cout << "x:" << new_x << " y:" << new_y << "\n";
                    if(ctrl_key_state){
                        pf.setTarget(new_x, new_y);
                    } else if(shift_key_state){
                        pf.setStart(new_x, new_y);
                    } else {
                        pf.obstacleToggle(new_x, new_y);
                    }
                }
            } else if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::LControl){
                    ctrl_key_state = true;
                } else if(event.key.code == sf::Keyboard::LShift){
                    shift_key_state = true;
                } else if(event.key.code == sf::Keyboard::Space){
                    if(!running){
                        running = true;
                    } else {
                        running = false;
                        success = false;
                        pf.reset();
                    }
                }
            } else if(event.type == sf::Event::KeyReleased){
                if(event.key.code == sf::Keyboard::LControl){
                    ctrl_key_state = false;
                } else if(event.key.code == sf::Keyboard::LShift){
                    shift_key_state = false;
                }
            } 
        }

        window.clear(sf::Color::White);
        field = pf.getNodeArray();
        for(int i=0; i < field.size(); i++){
            for(int j=0; j < field[0].size(); j++){
                sf::RectangleShape rect(sf::Vector2f(field_size, field_size));
                if(field[i][j].is_start == true){
                    rect.setFillColor(sf::Color(206, 255, 150));
                } else if(field[i][j].is_target == true){
                    rect.setFillColor(sf::Color(210, 100, 100));
                } else if(field[i][j].is_obstacle){
                    rect.setFillColor(sf::Color(90, 90, 90));
                }  else if(field[i][j].is_path){
                    rect.setFillColor(sf::Color(125, 125, 200));
                }  else if(field[i][j].visited){
                    rect.setFillColor(sf::Color(125, 200, 200));
                } else {
                    rect.setFillColor(sf::Color(206, 210, 200));
                }
                rect.setPosition(draw_origin_offset + i * (field_size+field_padding), draw_origin_offset + j * (field_size + field_padding));
                rect.setOutlineThickness(1);
                rect.setOutlineColor(sf::Color(100, 100, 100));
                window.draw(rect);
            }
        }
        if(success == false && running == true){
            success = pf.processNextNode();
            if (success){
                pf.drawPath();
            }
        } 
        window.display();
    }
    return 0;
}