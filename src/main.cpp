#include <SFML/Graphics.hpp>
#include <vector>
#include <stack>
#include <random>
#include <ctime>

class ParticleSystem : public sf::Drawable, public sf::Transformable
{
public:
    ParticleSystem(unsigned int count, unsigned int maxLifetimeSeconds) : m_particles(count), m_vertices(sf::PrimitiveType::Points, count)
    {
        m_lifetime = sf::seconds(maxLifetimeSeconds);
    }

    void setEmitter(sf::Vector2f position)
    {
        m_emitter = position;
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
        m_vertices[index].position = m_emitter;
    }

    std::vector<Particle> m_particles;
    sf::VertexArray       m_vertices;
    sf::Time              m_lifetime;
    sf::Vector2f          m_emitter;
};

class IndigoParticleSystem : public ParticleSystem
{   
public:
    IndigoParticleSystem(unsigned int count, unsigned int maxLifetimeSeconds) : ParticleSystem(count, maxLifetimeSeconds)
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
    EmeraldParticleSystem(unsigned int count, unsigned int maxLifetimeSeconds) : ParticleSystem(count, maxLifetimeSeconds)
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
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Particles");

    // create the particle system
    ParticleSystem particles(2000, 5);
    IndigoParticleSystem staticParticles(3000, 3);
    staticParticles.setEmitter({0, 300});
    EmeraldParticleSystem mirroringParticles(2500, 4);
    mirroringParticles.setEmitter({800, 300});

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
        particles.setEmitter(window.mapPixelToCoords(mouse));

        // update it
        sf::Time elapsed = clock.restart();
        particles.update(elapsed);
        staticParticles.update(elapsed);
        mirroringParticles.setEmitter(mirroringParticles.getPosition() - window.mapPixelToCoords(mouse) + sf::Vector2f(800, 600));
        mirroringParticles.update(elapsed);

        // draw it
        window.clear();
        window.draw(particles);
        window.draw(staticParticles);
        window.draw(mirroringParticles);
        window.display();
    }
}