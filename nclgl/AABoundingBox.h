#pragma once
#include "BoundingBox.h"
class AABoundingBox :
	public BoundingBox
{
public:
	AABoundingBox(Matrix4 t, Vector3 o) : BoundingBox(t, o) {}
	virtual void ExpendVolume(BoundingVolume* childBoundingVolume) override;
	virtual void GenerateBoundingVolume(const Mesh& m, Matrix4 modelMatrix) override;
	virtual void Update(Matrix4 newTrans) override { transform = newTrans; centre = transform.GetPositionVector(); } // without scale
	void SetCentre(Vector3 centre) { centre = centre; }
	Vector3 GetCentre() const { return centre; }
	void Draw() const;
	Matrix4 GetModelMatrix() const override;

protected:
	Vector3 centre;
	Vector3 minCorner;
	Vector3 maxCorner;
};

