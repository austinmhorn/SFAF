//
//  Button.hpp
//  leafy
//
//  Created by Austin Horn on 1/29/23.
//  Copyright © 2023 Austin Horn. All rights reserved.
//

#ifndef Button_hpp
#define Button_hpp

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <leafy/UIElement.hpp>
#include <leafy/Engine/Resources.hpp>
#include <leafy/Shapes/PolygonShape.hpp>
#include <leafy/Shapes/RoundedRectangleShape.hpp>
#include <leafy/Shapes/StadiumShape.hpp>

#include <exception>
#include <map>         // std::map
#include <type_traits> // std::is_same, std::remove_reference
#include <functional>  // std::function

namespace leafy
{

template <typename T>
class LEAFY_API Button  
    : public UIElement
{
    public:

        /// @brief 
        enum class Function 
            : std::size_t
        {
            MouseEnter = 0,
            MouseLeave = 1,
            ClickedOn  = 2,
            ClickedOff = 3,
        };

        /// @brief Represents alignment position of text within shape
        enum class TextAlignment 
            : std::size_t
        {
            Centered = 0, 
            Top      = 1,
            Right    = 2,
            Bottom   = 3,
            Left     = 4,
        };

        /// @brief Map type of interaction callback functions
        typedef std::map<Function, std::function<void()>> FunctionMap;

        /////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Constructor
        /// \param shape Derived sf::Shape object; required [even if shape is disabled] to deduce T
        /////////////////////////////////////////////////////////////////////////////////////////////
        explicit Button(const T& shape = T());

        //////////////////////////
        /// \brief Destructor
        //////////////////////////
        ~Button() override = default;

        /////////////////////////////////////////////////
        /// @brief Set the position of Button
        /// @param position 
        /////////////////////////////////////////////////
        void setPosition(const sf::Vector2f& position);

        /////////////////////////////////////////////////
        /// @brief Get the position of the Button
        /// @return Coordinate position in the window
        /////////////////////////////////////////////////
        const sf::Vector2f& getPosition() const;

        void setShapeFillColor(const sf::Color& color);
        void setShapeOutlineColor(const sf::Color& color);
        void setShapeOutlineThickness(float thickness);

        void setWillDrawShape(bool willDraw);

        void setTextString(const std::string& string);
        void setNumberTextLines(unsigned int lines);
        void setTextFillColor(const sf::Color& color);

        void setMouseEnterFunction(std::function<void()> function);
        void setMouseLeaveFunction(std::function<void()> function);
        void setMouseClickOnFunction(std::function<void()> function);
        void setMouseClickOffFunction(std::function<void()> function);

        bool contains(const sf::Vector2f& point) const override;
        void handleEvent(sf::RenderWindow& window, sf::Event event) override;

        /////////////////////////////////////////////////////////////////////
        /// @brief Set size for shapes with rectangular geometry
        /// @param size New size width and height 
        /////////////////////////////////////////////////////////////////////
        template <typename Rect = T,
            typename std::enable_if<std::is_same<Rect, sf::RectangleShape>::value, int>::type = 0>
        void setSize(const sf::Vector2f& size)
        {
            UIElement::setSize( size );
            m_shape.setSize( m_size );
            updateAlignment();
        }

        template <typename RoundedRect = T,
            typename std::enable_if<std::is_same<RoundedRect, sf::RoundedRectangleShape>::value, int>::type = 0>
        void setSize(const sf::Vector2f& size)
        {
            UIElement::setSize( size );
            m_shape.setSize( m_size );
            updateAlignment();
        }

        template <typename Stadium = T,
            typename std::enable_if<std::is_same<Stadium, sf::StadiumShape>::value, int>::type = 0>
        void setSize(const sf::Vector2f& size)
        {
            UIElement::setSize( size );
            m_shape.setSize( m_size );
            updateAlignment();
        }

        /////////////////////////////////////////////////////////////////////////
        /// @brief Get size of rectangular button
        /// @return Width and height of button
        /// @details Enabled if T is equivalent to any of the following types
        /// - RectangleShape
        /// - RoundedRectangleShape
        /// - StadiumShape
        /////////////////////////////////////////////////////////////////////////
        template <typename Rect = T,
            typename std::enable_if<std::is_same<Rect, sf::RectangleShape>::value, int>::type = 0>
        const sf::Vector2f& getSize() const { return UIElement::getSize(); }
        template <typename RoundedRect = T,
            typename std::enable_if<std::is_same<RoundedRect, sf::RoundedRectangleShape>::value, int>::type = 0>
        const sf::Vector2f& getSize() const { return UIElement::getSize(); }
        template <typename Stadium = T,
            typename std::enable_if<std::is_same<Stadium, sf::StadiumShape>::value, int>::type = 0>
        const sf::Vector2f& getSize() const { return UIElement::getSize(); }

        /////////////////////////////////////////////////////////////////////
        /// @brief Set radius for shapes with symmetric circular geometry
        /// @param radius New radius as float
        /// @details Enabled if type T is a sf::CircleShape
        /////////////////////////////////////////////////////////////////////
        template <typename Circle = T,
            typename std::enable_if<std::is_same<Circle, sf::CircleShape>::value, int>::type = 0>
        void setRadius(float radius)
        {
            UIElement::setRadius( radius );
            m_shape.setRadius( m_size.x );
            updateAlignment();
        }

        /////////////////////////////////////////////////////////////////////
        /// @brief Get radius of circular button
        /// @return Radius of button
        /// @details Enabled if type T is a sf::CircleShape
        /////////////////////////////////////////////////////////////////////
        template <typename Circle = T,
            typename std::enable_if<std::is_same<Circle, sf::CircleShape>::value, int>::type = 0>
        float getRadius() const { return UIElement::getRadius(); }

        /////////////////////////////////////////////////////////////////////
        /// @brief Set X and Y radius for shapes with convex polygon geometry
        /// @param radius New X and Y radius
        /// @details Enabled if type T is a sf::PolygonShape
        /////////////////////////////////////////////////////////////////////
        template <typename Polygon = T,
            typename std::enable_if<std::is_same<Polygon, sf::PolygonShape>::value, int>::type = 0>
        void setPolygonRadius(const sf::Vector2f& radius)
        {
            UIElement::setPolygonRadius( radius );
            m_shape.setRadius( m_size );
            updateAlignment();
        }

        /////////////////////////////////////////////////////////////////////
        /// @brief Get X and Y radius of convex polygon button
        /// @return X and Y radius of 
        /// @details Enabled if type T is a sf::PolygonShape
        /////////////////////////////////////////////////////////////////////
        template <typename Polygon = T,
            typename std::enable_if<std::is_same<Polygon, sf::PolygonShape>::value, int>::type = 0>    
        const sf::Vector2f& getPolygonRadius() const
            { return UIElement::getPolygonRadius(); }

    private:

        ///////////////////////////////////////////////
        /// @brief Positions text inside shape
        ///////////////////////////////////////////////
        void updateAlignment();

        void mouseEnter() override;
        void mouseLeave() override;
        void mouseClick() override;
        
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        T             m_shape;            // T is a derived sf::Shape
        sf::Text      m_label;             // Text label of button
        bool          m_drawShape;
        bool          m_translucentHover;
        FunctionMap   m_funcs;
        TextAlignment m_alignment;
        sf::Texture   m_texture;
};

//////////////////////////////////////
/// @brief Define most common types
//////////////////////////////////////

using RectangleButton = Button<sf::RectangleShape>;
using CircleButton = Button<sf::CircleShape>;
using PolygonButton = Button<sf::PolygonShape>;
using RoundedRectangleButton = Button<sf::RoundedRectangleShape>;
using StadiumButton = Button<sf::StadiumShape>;

}

/* 
    - Method 1
        • Simple method; Declare a button using a derived sf::Shape 
        • Button stadiumButton = Button(sf::StadiumShape()); 

    - Method 2
        • Ok; But needs parenthesis around arguement to declare a variable
        • Button stadiumButton( (sf::StadiumShape()) );       

    - Method 3
    // Pass a previously created shape to be copied
        sf::StadiumShape stadiumShape;        
        Button stadiumButton(stadiumShape);                 
*/

#endif /* Button_hpp */
