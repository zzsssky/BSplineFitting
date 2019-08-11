#pragma  once

#include <Eigen/Core>
#include <vector>
#include <map>

using namespace std;

class OpenCubicBSplineCurve
{

public:
	typedef std::pair<int, double> Parameter;

	OpenCubicBSplineCurve( double interval = 0.001 )
		: interval_(interval)
	{

	}

	~OpenCubicBSplineCurve() {
		clear();
	}

	unsigned int nb_control()  const { return controls_.size(); }

	unsigned int nb_segment()  const { return controls_.size()-3; }

	//////////////////////////////////////////////////////////////////////////
	// compute the x ,y position of current parameter
	//////////////////////////////////////////////////////////////////////////
	Eigen::Vector2d getPos(const Parameter& para) const;

	//////////////////////////////////////////////////////////////////////////
	// compute the first differential
	//////////////////////////////////////////////////////////////////////////
	Eigen::Vector2d getFirstDiff( const Parameter& para) const ;

	//////////////////////////////////////////////////////////////////////////
	// compute the second differential
	//////////////////////////////////////////////////////////////////////////
	Eigen::Vector2d getSecondDiff( const Parameter& para) const ;

	//////////////////////////////////////////////////////////////////////////
	// compute the curvature
	//////////////////////////////////////////////////////////////////////////
	double getCurvature( const Parameter& para) const ;


	//////////////////////////////////////////////////////////////////////////
	// compute the unit tangent vector
	//////////////////////////////////////////////////////////////////////////
	Eigen::Vector2d getTangent( const Parameter &para ) const ;


	//////////////////////////////////////////////////////////////////////////
	// compute the unit Normal vector
	//////////////////////////////////////////////////////////////////////////
	Eigen::Vector2d getNormal( const Parameter &para) const;

	//////////////////////////////////////////////////////////////////////////
	// compute the Curvature center ( rho = k)
	//////////////////////////////////////////////////////////////////////////
	Eigen::Vector2d getCurvCenter( const Parameter &para) const;

	///////////////////////////////////////////////////////////////////////////
	// compute the foot print
	//////////////////////////////////////////////////////////////////////////
	double findFootPrint( const vector<Eigen::Vector2d>& givepoints,
		vector<Parameter>& footPrints) const ;

	//////////////////////////////////////////////////////////////////////////
	// find the coff vector
	//////////////////////////////////////////////////////////////////////////
	Eigen::VectorXd getCoffe( const Parameter& para) const ;

	//////////////////////////////////////////////////////////////////////////
	// set the control points and compute a uniform spatial partition of the data points
	//////////////////////////////////////////////////////////////////////////
	void setNewControl( const vector<Eigen::Vector2d>& controlPs);

	//////////////////////////////////////////////////////////////////////////
	// check if two point is on same side. para is foot print of p1
	//////////////////////////////////////////////////////////////////////////
	bool checkSameSide( Eigen::Vector2d p1,  Eigen::Vector2d p2, Eigen::Vector2d neip);

	const vector<Eigen::Vector2d>& getControls() const {return controls_;}
	const vector<Eigen::Vector2d>& getSamples() const { return positions_; }


	Eigen::MatrixXd getSIntegralSq( );
	Eigen::MatrixXd getFIntegralSq( );

	void getDistance_sd( const Eigen::Vector2d& point, const Parameter& para, Eigen::MatrixXd& ehm, Eigen::VectorXd& ehv );
	void getDistance_pd( const Eigen::Vector2d& point, const Parameter& para, Eigen::MatrixXd& ehm, Eigen::VectorXd& ehv );

	int local2GlobalIdx( int segId, int localIdx);
	Parameter  getPara( int index ) const ;

private:
	void clear()
	{
		controls_.clear();
		positions_.clear();
	}


	//////////////////////////////////////////////////////////////////////////
	//winding number test for a point in a polygon
	// softSurfer (www.softsurfer.com)
	//////////////////////////////////////////////////////////////////////////
	bool checkInside( Eigen::Vector2d p);

	//////////////////////////////////////////////////////////////////////////
	// tests if a point is Left|On|Right of an infinite line.
	//////////////////////////////////////////////////////////////////////////
	int isLeft( Eigen::Vector2d p0, Eigen::Vector2d p1, Eigen::Vector2d p2);


private:
	double interval_;
	std::vector<Eigen::Vector2d> controls_;
	std::vector<Eigen::Vector2d> positions_;

};
