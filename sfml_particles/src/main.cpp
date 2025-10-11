#include <SFML/Graphics.hpp>
#include <vector>
#include <stack>
#include <random>
#include <ctime>

class AbstractEmitter {
public:
    virtual ~AbstractEmitter() = default;
    virtual sf::Vector2f getPosition() = 0;
};

class StaticEmitter : public AbstractEmitter
{   
public:
    StaticEmitter(sf::Vector2f position) 
        : m_position(position)
    {
    }

    sf::Vector2f getPosition() override
    {
        return m_position;          
    }
private:
    sf::Vector2f m_position;
};  


class FollowTheMouseEmitter : public AbstractEmitter
{   
public:
    FollowTheMouseEmitter(sf::RenderWindow &window) 
        : m_window(window)
    {
    }

    sf::Vector2f getPosition() override
    {
        sf::Vector2i mouse = sf::Mouse::getPosition(m_window);
        return m_window.mapPixelToCoords(mouse);      
    }
private:
    sf::RenderWindow &m_window;
};  

class MirroringEmitter : public AbstractEmitter
{   
public:
    MirroringEmitter(sf::RenderWindow &window) 
        : m_window(window)
    {
    }

    sf::Vector2f getPosition() override
    {
        sf::Vector2i mouse = sf::Mouse::getPosition(m_window);
        return m_window.mapPixelToCoords(sf::Vector2i(mouse.y, mouse.x));   
    }
private:
    sf::RenderWindow &m_window;
};

class ParticleSystem : public sf::Drawable, public sf::Transformable
{
public:
    ParticleSystem(unsigned int count, unsigned int maxLifetimeSeconds, AbstractEmitter& emitter)
        : m_particles(count), m_vertices(sf::PrimitiveType::Points, count), m_emitter(emitter)
    {
        m_lifetime = sf::seconds(maxLifetimeSeconds);
    }

    void updatePosition()
    {
        m_position = m_emitter.getPosition();
    }

    void update(sf::Time elapsed)
    {
        for (std::size_t i = 0; i < m_particles.size(); ++i)
        {
            // update the particle lifetime
            Particle& p = m_particles[i];
            p.lifetime -= elapsed;

            // if the particle is dead, respawn it
            if (p.lifetime <= sf::Time::Zero)
                resetParticle(i);

            // update the position of the corresponding vertex
            m_vertices[i].position += p.velocity * elapsed.asSeconds();

            // update the alpha (transparency) of the particle according to its lifetime
            float ratio           = p.lifetime.asSeconds() / m_lifetime.asSeconds();
            changeColor(m_vertices[i], ratio);
        }
    }

    virtual void changeColor(sf::Vertex &particle, float ratio)
    {
        particle.color.a = static_cast<std::uint8_t>(ratio * 255);
        particle.color.r = 255;
        particle.color.g = static_cast<std::uint8_t>(ratio * 255);
        particle.color.b = 100;
    }

private:
    struct Particle
    {
        sf::Vector2f velocity;
        sf::Time     lifetime;
    };

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        // apply the transform
        states.transform *= getTransform();

        // our particles don't use a texture
        states.texture = nullptr;

        // draw the vertex array
        target.draw(m_vertices, states);
    }

    void resetParticle(std::size_t index)
    {
        // create random number generator
        static std::random_device rd;
        static std::mt19937       rng(rd());

        // give a random velocity and lifetime to the particle
        const sf::Angle angle       = sf::degrees(std::uniform_real_distribution(0.f, 360.f)(rng));
        const float     speed       = std::uniform_real_distribution(50.f, 100.f)(rng);
        m_particles[index].velocity = sf::Vector2f(speed, angle);
        m_particles[index].lifetime = sf::milliseconds(std::uniform_int_distribution(1000, m_lifetime.asMilliseconds())(rng));

        // reset the position of the corresponding vertex
        m_vertices[index].position = m_position;
    }

    std::vector<Particle> m_particles;
    sf::VertexArray       m_vertices;
    sf::Time              m_lifetime;
    sf::Vector2f          m_position;
    AbstractEmitter&      m_emitter;
};

class IndigoParticleSystem : public ParticleSystem
{   
public:
    IndigoParticleSystem(unsigned int count, unsigned int maxLifetimeSeconds, AbstractEmitter& emitter)
        : ParticleSystem(count, maxLifetimeSeconds, emitter)
    {
    }   

protected:
    virtual void changeColor(sf::Vertex &particle, float ratio)
    {
        particle.color.a = static_cast<std::uint8_t>(ratio * 255);
        particle.color.r = 100;
        particle.color.g = static_cast<std::uint8_t>(ratio * 255);
        particle.color.b = 255;
    }    
};

class EmeraldParticleSystem : public ParticleSystem
{   
public:
    EmeraldParticleSystem(unsigned int count, unsigned int maxLifetimeSeconds, AbstractEmitter& emitter)
        : ParticleSystem(count, maxLifetimeSeconds, emitter)
    {
    }
protected:
    virtual void changeColor(sf::Vertex &particle, float ratio)
    {
        particle.color.a = static_cast<std::uint8_t>(ratio * 255);
        particle.color.r = 100;
        particle.color.g = 255;
        particle.color.b = static_cast<std::uint8_t>(ratio * 255);
    }   
};

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode({800, 800}), "Particles");
    // Static Emmiter 
    StaticEmitter staticEmitter(sf::Vector2f(400, 200));
    // create the emitter
    FollowTheMouseEmitter mouseEmitter(window);
    // Mirroring Emitter 
    MirroringEmitter mirroringEmitter(window);

    // create the particle system
    ParticleSystem particles(10000, 5, mouseEmitter);
    IndigoParticleSystem staticParticles(10000, 7, staticEmitter);
    EmeraldParticleSystem mirroringParticles(10000, 4, mirroringEmitter);

    // create a clock to track the elapsed time
    sf::Clock clock;

    // run the main loop
    while (window.isOpen())
    {
        // handle events
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // make the particle system emitter follow the mouse
        sf::Vector2i mouse = sf::Mouse::getPosition(window);        
        // particles.setPosition(window.mapPixelToCoords(mouse));

        // update it
        sf::Time elapsed = clock.restart();
        particles.updatePosition();
        staticParticles.updatePosition();
        mirroringParticles.updatePosition();
        particles.update(elapsed);
        staticParticles.update(elapsed);        
        mirroringParticles.update(elapsed);

        // draw it
        window.clear();
        window.draw(particles);
        window.draw(staticParticles);
        window.draw(mirroringParticles);
        window.display();
    }
}