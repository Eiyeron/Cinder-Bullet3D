//
//  ConstraintHinge.h
//  BulletSourceTest
//
//  Created by Ryan Bartley on 4/7/14.
//
//

#pragma once

#include "Cinder-Bullet3D/Common.h"
#include "Cinder-Bullet3D/RigidBody.h"
#include "Cinder-Bullet3D/ConstraintBase.h"

namespace bullet {

	
class ConstraintHinge : public ConstraintBase {
public:
	
	struct Format : ConstraintBase::Format {
		Format();
		
		Format& objA( const RigidBodyRef &objA ) { mObjA = objA; return *this; }
		Format& objB( const RigidBodyRef &objB ) { mObjB = objB; return *this; }
		Format& localAOrigin( const ci::Vec3f &origin ) { mLocalA.setOrigin( toBullet( origin ) ); return *this; }
		Format& localARot( const ci::Quatf &rot ) { mLocalA.setBasis( toBullet( rot.toMatrix33() ) ); return *this; }
		Format& localBOrigin( const ci::Vec3f &origin ) { mLocalB.setOrigin( toBullet( origin ) ); return *this; }
		Format& localBRot( const ci::Quatf &rot ) { mLocalB.setBasis( toBullet( rot.toMatrix33() ) ); return *this; }
		Format& localAtrans( const btTransform &trans ) { mLocalA = trans; return *this; }
		Format& localBtrans( const btTransform &trans ) { mLocalB = trans; return *this; }
		Format& useReferenceFrameA( bool use ) { mUseReferenceFrameA = use; return *this; }
		
	protected:
		btTransform mLocalA, mLocalB;
		bool mUseReferenceFrameA;
		
		friend class ConstraintHinge;
	};
	
	static ConstraintHingeRef create( const Format &format );
	
	btHingeConstraintRef getHingeConstraint()
	{
		return std::static_pointer_cast<btHingeConstraint>(mConstraint);
	}
	
	inline void setLimit( btScalar low, btScalar high )
	{
		getHingeConstraint()->setLimit( low, high );
	}
	
	~ConstraintHinge() {}
	
private:
	ConstraintHinge( const Format &format );
};
	
}
