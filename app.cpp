#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "Boids/Boid.hpp"
#include "Boids/BoidController.hpp"
#include "Forces/Local/LocalForces.hpp"
#include "Forces/Global/GlobalForces.hpp"

using namespace ci;
using namespace ci::app;


class BoidsApp : public App
{

public:
    void draw () override;

    void update () override;

    void mouseDrag ( MouseEvent ) override;

    void keyDown ( KeyEvent ) override;

    void setup () override;

private:
    gl::BatchRef mCirc;
    std::unique_ptr<BoidController> controller{};
    double lastTimestamp{};
};


void BoidsApp::setup ()
{
  setFullScreen( false );

  controller = std::make_unique<BoidController>();

  controller->addForce( std::make_unique<DirectionalForce>( 45.f ));
  controller->addForce( std::make_unique<CenterOfMassForce>( 45.f ));
  controller->addForce( std::make_unique<RepulsiveForce>( 45.f ));
  controller->addForce( std::make_unique<MaxVelocityForce>( 10.f ));
  controller->addForce( std::make_unique<BoundaryForce>( 300, 1200, 300, 500, 0.5f ));

  auto color_shader_def = gl::ShaderDef().color();
  gl::GlslProgRef shader = gl::getStockShader( color_shader_def );
  mCirc = gl::Batch::create( geom::Circle().radius( 3.0f ), shader );
  lastTimestamp = getElapsedSeconds();
}



void BoidsApp::mouseDrag ( MouseEvent event )
{
  controller->addBoid( vec2{ event.getX(), event.getY() } );
}


void BoidsApp::keyDown ( KeyEvent event )
{
  switch ( event.getCode())
  {
    case KeyEvent::KEY_q:
      quit();

    case KeyEvent::KEY_b:
      controller->addForce( std::make_unique<ObstacleForce>( getMousePos(), 100.f ));
      break;

    default:
      break;
  }
}


void BoidsApp::update ()
{
  double current_timestamp = getElapsedSeconds();
  double dt = current_timestamp - lastTimestamp;
  lastTimestamp = current_timestamp;

  controller->update( static_cast<float>(40 * dt));
}


void BoidsApp::draw ()
{
  gl::clear( Color( 0, 0, 0 ), true );
  controller->draw( mCirc );
  gl::drawString( std::to_string( getAverageFps()), vec2{ 10, 10 } );
  gl::drawString( std::to_string( controller->getNumBoids()), vec2{ 10, 20 } );
}


CINDER_APP( BoidsApp, RendererGl )
