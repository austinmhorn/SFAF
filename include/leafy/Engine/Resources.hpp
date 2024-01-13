//
//  Resources.hpp
//  leafy
//
//  Created by Austin Horn on 9/30/22.
//  Copyright © 2022 Austin Horn. All rights reserved.
//

#ifndef Assets_hpp
#define Assets_hpp

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Color.hpp>

#include <iostream>   // std::cin, std::cout
#include <string>   
//#include <new>        // std::bad_alloc
//#include <cmath>      // std::ceil, std::log
//#include <cassert>    // assert

#include <leafy/SmartMouse.hpp>

#if defined( LEAFY_INCLUDE_FONT )
#include <leafy/Engine/Sansation.hpp>
#endif


namespace leafy
{

    // Images
    static const std::string __filepath_domino = "examples/data/images/domino.png";

    ////////////////////////////////////////////////////////////
    /// \namespace Textures
    ///
    /// \brief
    ////////////////////////////////////////////////////////////
    namespace Textures 
    {

        static sf::Texture __load_texture(const std::string& filepath) 
        {
            static sf::Texture texture;
            try 
            {
                if ( !texture.loadFromFile(filepath) )
                    throw std::runtime_error("Failed loading texture: ");
            }
            catch(const std::runtime_error &e) 
            {
                std::cerr << "std::runtime_error::what(): " << e.what() << filepath << std::endl;
            }
            return texture;
        }

        static const sf::Texture __load_domino()
        {
            return __load_texture(__filepath_domino);
        }
    } // MARK: End of namespace 'Textures'

    struct Resources
    {
        static const sf::Font Sansation;
        
        static const sf::Color Gray;
        static const sf::Color DarkGreen;
        static const sf::Color DarkRed;
        static const sf::Color DarkPurple;
        static const sf::Color LightBlue;
        static const sf::Color Seafoam;
        static const sf::Color LightGreen;
        static const sf::Color Peach;
        static const sf::Color Tan;
        static const sf::Color Pink;
        static const sf::Color LightPurple;
        static const sf::Color Orange;
        static const sf::Color DarkBlue;

        static SmartMouse smartmouse;
    };

}

#endif /* Assets_hpp */
