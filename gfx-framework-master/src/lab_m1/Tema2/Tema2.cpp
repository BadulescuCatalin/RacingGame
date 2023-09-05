#include "lab_m1/Tema2/Tema2.h"
#include "lab_m1/Tema2/tema_transform3D.h"


#include "core/engine.h"
#include "utils/gl_utils.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}


void Tema2::Init()
{
	renderCameraTarget = false;
	polygonMode = GL_FILL;

	camera = new implemented2::Camera2();
	camera->Set(glm::vec3(0, 0.5, 3.5f), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	camera2 = new implemented2::Camera2();
	camera2->Set(camera->GetTargetPosition() + glm::vec3(0, 10, 0), camera->GetTargetPosition() , glm::vec3(1, 0, 0));
	
	cameraPos = camera->position;
	cameraFp = new implemented2::Camera2();
	cameraFp->Set(camera->GetTargetPosition(), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	cameraFp->position = camera->GetTargetPosition() - camera->forward * 0.60f + glm::vec3(0, 0.15, 0);

	cameraFp->distanceToTarget = 0;
	cameraBack = new implemented2::Camera2();		
	cameraBack->Set(-camera->GetTargetPosition(), glm::vec3(0, -0.1, 0), glm::vec3(0, 1, 0));
	cameraBack->position = camera->GetTargetPosition() + camera->forward * 0.60f + glm::vec3(0, 0.25, 0);


	{
		// puncte XOZ pe mapa
		vector <VertexFormat> mapPoints{
			VertexFormat(glm::vec3(-4.78, 0 , 6.16)), // A
			VertexFormat(glm::vec3(-6.22, 0, 6.72)), // B
			VertexFormat(glm::vec3(-7.66, 0, 6.34)),//C
			VertexFormat(glm::vec3(-8.28, 0, 5.54)),//P1
			VertexFormat(glm::vec3(-8.97, 0, 4.65)),//D
			VertexFormat(glm::vec3(-9.16, 0, 2.94)),//E
			VertexFormat(glm::vec3(-9.41, 0, 1.94)),//W1
			VertexFormat(glm::vec3(-9.72, 0, 0.74)),//F
			VertexFormat(glm::vec3(-9.96, 0, 0)),//Z1
			VertexFormat(glm::vec3(-10.32, 0 ,-1.08)),//G
			VertexFormat(glm::vec3(-10.29, 0 ,-1.88)),//h2
			VertexFormat(glm::vec3(-9.99, 0 ,-2.46)),//T2
			VertexFormat(glm::vec3(-9.78, 0, -2.74)),//H
			VertexFormat(glm::vec3(-8.32, 0,  -3.8)),//S
			VertexFormat(glm::vec3(-6.94, 0, -4.46)),//I
			VertexFormat(glm::vec3(-5.86, 0, -4.34)),//B2
			VertexFormat(glm::vec3(-4.6, 0, -4.16)),//J
			VertexFormat(glm::vec3(-3.7, 0, -4.64)),//A2
			VertexFormat(glm::vec3(-2.62, 0, -5.18)),//K
			VertexFormat(glm::vec3(-1.22, 0, -5.54)),//C1
			VertexFormat(glm::vec3(0.08, 0, -5.44)),//D1
			VertexFormat(glm::vec3(0.7, 0, -4.82)),//E1
			VertexFormat(glm::vec3(0.92, 0, -3.72)),//L
			VertexFormat(glm::vec3(0.26, 0, -2.66)),//C2
			VertexFormat(glm::vec3(-0.34, 0, -1.66)),//M
			VertexFormat(glm::vec3(-1.36, 0, -0.6)),//E2
			VertexFormat(glm::vec3(-2.54, 0, 0.68)),//N
			VertexFormat(glm::vec3(-2.62, 0, 2)),//O
			VertexFormat(glm::vec3(-2.04, 0, 2.74)),//P
			VertexFormat(glm::vec3(-1.32, 0, 3)),//R2
			VertexFormat(glm::vec3(-0.55, 0, 2.84)),//S2
			VertexFormat(glm::vec3(0.14, 0, 2.46)),//R
			VertexFormat(glm::vec3(2.27, 0, 1.34)),//I2
			VertexFormat(glm::vec3(2.69, 0, 1.08)),//G2
			VertexFormat(glm::vec3(3.07, 0, 0.74)),//F2
			VertexFormat(glm::vec3(3.45333, 0, 0.14)),//Q
			VertexFormat(glm::vec3(4.09, 0, -0.35)),//J2
			VertexFormat(glm::vec3(4.51, 0, -1.15)),//K2
			VertexFormat(glm::vec3(4.69, 0, -2.02)),//L2
			VertexFormat(glm::vec3(5.36, 0, -2.78)),//M2
			VertexFormat(glm::vec3(6, 0, -4)),//T
			VertexFormat(glm::vec3(6.88, 0, -4.81)),//N2
			VertexFormat(glm::vec3(8.34, 0, -5.32)),//U
			VertexFormat(glm::vec3(9.98, 0, -5.8)),//F1
			VertexFormat(glm::vec3(11.24, 0, -6.1)),//G1
			VertexFormat(glm::vec3(11.98, 0, -5.84)),//H1
			VertexFormat(glm::vec3(12.8, 0, -5.12)),//I1
			VertexFormat(glm::vec3(13.26, 0, -3.94)),//J1
			VertexFormat(glm::vec3(13.48, 0, -2.18)),//V
			VertexFormat(glm::vec3(13.44, 0, -1.14)),//Q2
			VertexFormat(glm::vec3(13.4, 0, 0.12)),//P2
			VertexFormat(glm::vec3(13.35, 0, 1.35)),//O2
			VertexFormat(glm::vec3(13.3, 0, 2.76)),//W
			VertexFormat(glm::vec3(12.66, 0, 3.6)),//K1
			VertexFormat(glm::vec3(11.48, 0, 3.98)),//L1
			VertexFormat(glm::vec3(10.6, 0, 3.96)),//M1
			VertexFormat(glm::vec3(9.28, 0, 3.34)),//N1
			VertexFormat(glm::vec3(7.82, 0, 3.36)),//O1
			VertexFormat(glm::vec3(6.89, 0, 3.58)),//V1
			VertexFormat(glm::vec3(5.94, 0, 3.81)),//U1
			VertexFormat(glm::vec3(4.8, 0, 4.08)),//Z
			VertexFormat(glm::vec3(3.28, 0, 4.7)),//S1
			VertexFormat(glm::vec3(1.86, 0, 5.32)),//R1
			VertexFormat(glm::vec3(0.44, 0, 5.86)),//A1
			VertexFormat(glm::vec3(-0.73, 0, 5.76)),//T1
			VertexFormat(glm::vec3(-2.08, 0, 5.46)),//B1
			VertexFormat(glm::vec3(-3.43, 0, 5.81)),//Q1
			VertexFormat(glm::vec3(-4.78, 0 , 6.16)),//A
			VertexFormat(glm::vec3(-6.22, 0, 6.72)),//B

		};
		vector<VertexFormat> outerInner;
		//vector<VertexFormat> inner;
		vector<VertexFormat> moreMapPoints;
		for (int i = 0; i < mapPoints.size()-2;++i) {
			glm::vec3 P1 = mapPoints[i].position;
			glm::vec3 P2 = mapPoints[i + 1].position;
			for (float j = 0; j <= 1; j+=0.05) {
				glm::vec3 newP = glm::mix(P1, P2, j);
				moreMapPoints.push_back(newP);
			}
		}
		moreMapPoints.push_back(moreMapPoints[0]);
		moreMapPoints.push_back(moreMapPoints[1]);
		
		float distRosu = 1.2;
		float distAlbastru = 1.2;
		float distObstacol = 0.6;
		for (int i = 0; i < moreMapPoints.size() - 1; ++i) {
			glm::vec3 P1 = (moreMapPoints[i].position);
			glm::vec3 P2 = (moreMapPoints[i + 1].position);
			P1.z *= -1;
			P2.z *= -1;
			glm::vec3 D = P2 - P1;
			glm::vec3 UP = glm::vec3(0, 1, 0);
			glm::vec3 P = glm::normalize(glm::cross(D, UP));
			glm::vec3 R = P1 + distRosu * P;
			glm::vec3 A = P1 - distAlbastru * P;
			glm::vec3 obstacol = P1 + distObstacol * P;
			glm::vec3 obstacol1 = obstacol;

			outerInner.push_back(VertexFormat(R, glm::vec3(0.4, 0.5, 0.5), glm::vec3(0.4, 0.5, 0.5)));
			outerInner.push_back(VertexFormat(A, glm::vec3(0.4, 0.5, 0.5), glm::vec3(0.4, 0.5, 0.5)));
			//if (i != 0) {
			//	directions.push_back(obstacol - prev);
			//}
			//posObstacol.push_back(obstacol);
			
			if (i % 20 == 0) {
			//	trees.push_back(R + P / 2.0f);
			//	trees.push_back(A - P / 2.0f);
			}
			R = P2 + distRosu * P;
			A = P2 - distAlbastru * P;
			
			obstacol = P2 + distObstacol * P;
			if (i != moreMapPoints.size() - 2) {
				//posObstacol.push_back(obstacol);
			}
			if (i % 20 == 0) {
			//	trees.push_back(R + P / 2.0f);
			//	trees.push_back(A - P / 2.0f);
			}
	//		outerInner.push_back(VertexFormat(R, glm::vec3(0.4, 0.5, 0.5), glm::vec3(0.4, 0.5, 0.5)));
		//	outerInner.push_back(VertexFormat(A, glm::vec3(0.4, 0.5, 0.5), glm::vec3(0.4, 0.5, 0.5)));
			//directions.push_back(obstacol - obstacol1);
			prev = obstacol;
			
		}



		for (int i = 0; i < mapPoints.size() - 1; ++i) {
			glm::vec3 P1 = (mapPoints[i].position);
			glm::vec3 P2 = (mapPoints[i + 1].position);
			P1.z *= -1;
			P2.z *= -1;
			glm::vec3 D = P2 - P1;
			glm::vec3 UP = glm::vec3(0, 1, 0);
			glm::vec3 P = glm::normalize(glm::cross(D, UP));
			glm::vec3 R = P1 + distRosu * P;
			glm::vec3 A = P1 - distAlbastru * P;
			glm::vec3 obstacol = P1 + distObstacol * P;
			glm::vec3 obstacol1 = obstacol;

			outerInner.push_back(VertexFormat(R, glm::vec3(0.4, 0.5, 0.5), glm::vec3(0.4, 0.5, 0.5)));
			outerInner.push_back(VertexFormat(A, glm::vec3(0.4, 0.5, 0.5), glm::vec3(0.4, 0.5, 0.5)));
			//if (i != 0) {
			//	directions.push_back(obstacol - prev);
			//}
			posObstacol.push_back(obstacol);

				trees.push_back(R + P / 2.0f);
				trees.push_back(A - P / 2.0f);
			
			R = P2 + distRosu * P;
			A = P2 - distAlbastru * P;

			obstacol = P2 + distObstacol * P;
			if (i != mapPoints.size() - 2) {
				//posObstacol.push_back(obstacol);
			}
				trees.push_back(R + P / 2.0f);
				trees.push_back(A - P / 2.0f);
			//		outerInner.push_back(VertexFormat(R, glm::vec3(0.4, 0.5, 0.5), glm::vec3(0.4, 0.5, 0.5)));
				//	outerInner.push_back(VertexFormat(A, glm::vec3(0.4, 0.5, 0.5), glm::vec3(0.4, 0.5, 0.5)));
			directions.push_back(obstacol - obstacol1);
			prev = obstacol;

		}


		distObstacol = 0.1;
		for (int i = moreMapPoints.size()-1; i >= 1; --i) {
			glm::vec3 P1 = (moreMapPoints[i].position);
			glm::vec3 P2 = (moreMapPoints[i - 1].position);
			P1.z *= -1;
			P2.z *= -1;
			glm::vec3 D = P2 - P1;
			glm::vec3 UP = glm::vec3(0, 1, 0);
			glm::vec3 P = glm::normalize(glm::cross(D, UP));
			glm::vec3 obstacol = P1 + distObstacol * P;
			//if (obstacol - prev == glm::vec3(0, 0, 0)) continue;
			//if (i != mapPoints.size()-1) {
				//directionsInv.push_back(obstacol - prev);
			//}

			//posObstacolInv.push_back(obstacol);
			glm::vec3 obstacol1 = obstacol;
			obstacol = P2 + distObstacol * P;
			//if (obstacol - obstacol1 == glm::vec3(0, 0, 0)) continue;
			//directionsInv.push_back(obstacol - obstacol1);

			if (i != 0) {
			//	posObstacolInv.push_back(obstacol);
			}

			
			prev = obstacol;
			if (i == 1) {
				P1 = (moreMapPoints[0].position);
				P2 = (moreMapPoints[moreMapPoints.size()-1].position);
				P1.z *= -1;
				P2.z *= -1;
				D = P2 - P1;
				UP = glm::vec3(0, 1, 0);
				P = glm::normalize(glm::cross(D, UP));
				obstacol = P1 + distObstacol * P;
				//directionsInv.push_back(obstacol - prev);
			}
		}



		for (int i = mapPoints.size() - 1; i >= 1; --i) {
			glm::vec3 P1 = (mapPoints[i].position);
			glm::vec3 P2 = (mapPoints[i - 1].position);
			P1.z *= -1;
			P2.z *= -1;
			glm::vec3 D = P2 - P1;
			glm::vec3 UP = glm::vec3(0, 1, 0);
			glm::vec3 P = glm::normalize(glm::cross(D, UP));
			glm::vec3 obstacol = P1 + distObstacol * P;
			
			posObstacolInv.push_back(obstacol);
			glm::vec3 obstacol1 = obstacol;
			obstacol = P2 + distObstacol * P;
			directionsInv.push_back(obstacol - obstacol1);
		}


		int idx = 0;
		vector<unsigned int> indices;
		for (int i = 0; i < outerInner.size() - 3; i += 2) {
			indices.push_back(i);
			indices.push_back(i + 1);
			indices.push_back(i + 3);
			TrianglePoints tr1, tr2;
			tr1.p1 = outerInner[i].position;
			tr1.p2 = outerInner[i + 1].position;
			tr1.p3 = outerInner[i + 3].position;
			indices.push_back(i);
			indices.push_back(i + 2);
			indices.push_back(i + 3);
			tr2.p1 = outerInner[i].position;
			tr2.p2 = outerInner[i + 2].position;
			tr2.p3 = outerInner[i + 3].position;
			triangles.push_back(tr1);
			triangles.push_back(tr2);
			idx += 2;
			if (idxStartTr != -1) {
				if (isPointInTriangle(tr1, camera->GetTargetPosition())) {

					idxStartTr = idx - 2;
				}
				else if (isPointInTriangle(tr2, camera->GetTargetPosition())) {
					idxStartTr = idx - 1;
				}
			}

			CreateMesh("pista", outerInner, indices);
		}
		for (int i = 0; i < trees.size(); ++i) {
			for(int j=0; j<triangles.size(); ++j)
				if (isPointInTriangle(triangles[j], trees[i]))
				{
					trees[i] = glm::vec3(1, 0, 1);
					break;
				}

		}
		{
			// XOZ iarba

			vector <VertexFormat> grassPoints{
				//VertexFormat(glm::vec3(-100, -0.001, 100), glm::vec3(0, 1, 0)),
				//VertexFormat(glm::vec3(100, -0.001, 100), glm::vec3(0, 1, 0)),
				//VertexFormat(glm::vec3(100, -0.001, -100), glm::vec3(0, 1, 0)),
				//VertexFormat(glm::vec3(-100, -0.001, -100), glm::vec3(0, 1, 0))

			};
			glm::vec3 susStanga = glm::vec3(-100, -0.001, 100);
			glm::vec3 susDreapta = glm::vec3(100, -0.001, 100);
			glm::vec3 josStanga = glm::vec3(-100, -0.001, -100);
			glm::vec3 josDreapta = glm::vec3(100, -0.001, -100);
			for (float i = 0; i <= 1; i += 0.00001) {
				glm::vec3 P = glm::mix(josStanga, susStanga, i);
				grassPoints.push_back(VertexFormat(P, glm::vec3(0, 1, 0)));
				P = glm::mix(josDreapta, susDreapta, i);
				grassPoints.push_back(VertexFormat(P, glm::vec3(0, 1, 0)));
				
			}
			vector<unsigned int> grassIndices{
//				0, 1, 2,
	//			2, 3, 0
			};
			for (int i = 0; i < grassPoints.size() - 2; i+=2) {
				grassIndices.push_back(i);
				grassIndices.push_back(i + 1);
				grassIndices.push_back(i + 3);
				grassIndices.push_back(i);
				grassIndices.push_back(i + 2);
				grassIndices.push_back(i + 3);

			}
			CreateMesh("iarba", grassPoints, grassIndices);
		}

		// Create a simple cube
		{
			vector<VertexFormat> verticesCube
			{
				VertexFormat(glm::vec3(-0.1, -0.12,  0.2), glm::vec3(0, 0.1, 0.1), glm::vec3(0, 0, 1)),
				VertexFormat(glm::vec3(0.1, -0.12,  0.2), glm::vec3(0.1, 0, 0.1), glm::vec3(0, 0, 1)),
				VertexFormat(glm::vec3(-0.1,  0.12,  0.2), glm::vec3(0.1, 0, 0), glm::vec3(1, 0, 1)),
				VertexFormat(glm::vec3(0.1,  0.12,  0.2), glm::vec3(0, 0.1, 0), glm::vec3(1, 0, 1)),
				VertexFormat(glm::vec3(-0.1, -0.12, -0.2), glm::vec3(0.1, 0.1, 0.1), glm::vec3(0, 0, 1)),
				VertexFormat(glm::vec3(0.1, -0.12, -0.2), glm::vec3(0, 0.1, 0.1), glm::vec3(0, 0, 1)),
				VertexFormat(glm::vec3(-0.1,  0.12, -0.2), glm::vec3(0.1, 0.1, 0), glm::vec3(1, 0, 1)),
				VertexFormat(glm::vec3(0.1,  0.12, -0.2), glm::vec3(0, 0, 0.1), glm::vec3(1, 0, 1)),
			};

			vector<unsigned int> indicesCube =
			{
				0, 1, 2,        1, 3, 2,
				2, 3, 7,        2, 7, 6,
				1, 7, 3,        1, 5, 7,
				6, 7, 4,        7, 5, 4,
				0, 4, 1,        1, 4, 5,
				2, 6, 4,        0, 2, 4,
			};

			CreateMesh("cube", verticesCube, indicesCube);
		}
		razaMasini = 0.2f;

		// Create a tree
		{
			vector<VertexFormat> verticesTree
			{
				// tree low

				VertexFormat(glm::vec3(-0.05, -0.1,  0.05) + glm::vec3(0, 0.1,  0), glm::vec3(0, 0.1, 0.1), glm::vec3(0.71, 0.4, 0.11)),
				VertexFormat(glm::vec3(0.05, -0.1,  0.05) + glm::vec3(0, 0.1,  0), glm::vec3(0.1, 0, 0.1), glm::vec3(0.71, 0.4, 0.11)),
				VertexFormat(glm::vec3(-0.05,  0.1,  0.05) + glm::vec3(0, 0.1,  0), glm::vec3(0.1, 0, 0), glm::vec3(0.71, 0.4, 0.11)),
				VertexFormat(glm::vec3(0.05,  0.1,  0.05) + glm::vec3(0, 0.1,  0), glm::vec3(0, 0.1, 0), glm::vec3(0.71, 0.4, 0.11)),
				VertexFormat(glm::vec3(-0.05, -0.1, -0.05) + glm::vec3(0, 0.1,  0), glm::vec3(0.1, 0.1, 0.1), glm::vec3(0.71, 0.4, 0.11)),
				VertexFormat(glm::vec3(0.05, -0.1, -0.05) + glm::vec3(0, 0.1,  0), glm::vec3(0, 0.1, 0.1), glm::vec3(0.71, 0.4, 0.11)),
				VertexFormat(glm::vec3(-0.05,  0.1, -0.05) + glm::vec3(0, 0.1,  0), glm::vec3(0.1, 0.1, 0), glm::vec3(0.71, 0.4, 0.11)),
				VertexFormat(glm::vec3(0.05,  0.1, -0.05) + glm::vec3(0, 0.1,  0), glm::vec3(0, 0, 0.1), glm::vec3(0.71, 0.4, 0.11)),

				//tree up
				VertexFormat(glm::vec3(-0.15, -0.12,  0.15) + glm::vec3(0, 0.1 * 3,  0), glm::vec3(0, 0.1, 0.1), glm::vec3(0, 0.5, 0.13)),
				VertexFormat(glm::vec3(0.15, -0.12,  0.15) + glm::vec3(0, 0.1 * 3,  0), glm::vec3(0.1, 0, 0.1), glm::vec3(0, 0.5, 0.13)),
				VertexFormat(glm::vec3(-0.15,  0.12,  0.15) + glm::vec3(0, 0.1 * 3,  0), glm::vec3(0.1, 0, 0), glm::vec3(0, 0.5, 0.13)),
				VertexFormat(glm::vec3(0.15,  0.12,  0.15) + glm::vec3(0, 0.1 * 3,  0), glm::vec3(0, 0.1, 0), glm::vec3(0, 0.5, 0.13)),
				VertexFormat(glm::vec3(-0.15, -0.12, -0.15) + glm::vec3(0, 0.1 * 3,  0), glm::vec3(0.1, 0.1, 0.1), glm::vec3(0, 0.5, 0.13)),
				VertexFormat(glm::vec3(0.15, -0.12, -0.15) + glm::vec3(0, 0.1 * 3,  0), glm::vec3(0, 0.1, 0.1), glm::vec3(0, 0.5, 0.13)),
				VertexFormat(glm::vec3(-0.15,  0.12, -0.15) + glm::vec3(0, 0.1 * 3,  0), glm::vec3(0.1, 0.1, 0), glm::vec3(0, 0.5, 0.13)),
				VertexFormat(glm::vec3(0.15,  0.12, -0.15) + glm::vec3(0, 0.1 * 3,  0), glm::vec3(0, 0, 0.1), glm::vec3(0, 0.5, 0.13)),

			};


			;
			vector<unsigned int> indicesTree =
			{
				0, 1, 2,        1, 3, 2,
				2, 3, 7,        2, 7, 6,
				1, 7, 3,        1, 5, 7,
				6, 7, 4,        7, 5, 4,
				0, 4, 1,        1, 4, 5,
				2, 6, 4,        0, 2, 4,

				0 + 8, 1 + 8, 2 + 8,        1 + 8, 3 + 8, 2 + 8,
				2 + 8, 3 + 8, 7 + 8,        2 + 8, 7 + 8, 6 + 8,
				1 + 8, 7 + 8, 3 + 8,        1 + 8, 5 + 8, 7 + 8,
				6 + 8, 7 + 8, 4 + 8,        7 + 8, 5 + 8, 4 + 8,
				0 + 8, 4 + 8, 1 + 8,        1 + 8, 4 + 8, 5 + 8,
				2 + 8, 6 + 8, 4 + 8,        0 + 8, 2 + 8, 4 + 8,
			};

			CreateMesh("tree", verticesTree, indicesTree);
		}

	}

	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
		Mesh* mesh2 = new Mesh("grass");
		mesh2->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "plane50.obj");
		meshes[mesh2->GetMeshID()] = mesh2;
	}

	// Create a shader program for drawing face polygon with the color of the normal
	{
		Shader* shader = new Shader("TemaShader");
		shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shadersTema", "VertexShaderTema.glsl"), GL_VERTEX_SHADER);
		shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shadersTema", "FragmentShaderTema.glsl"), GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}


	glm::ivec2 resolution = window->GetResolution();
	miniViewportArea = ViewportArea(10, 10, resolution.x / 3.f, resolution.y / 3.f);
	miniViewportArea2 = ViewportArea(10, 10, resolution.x / 4.f, resolution.y / 5.f);
	// TODO(student): After you implement the changing of the projection
	// parameters, remove hardcodings of these parameters
	projectionMatrix = glm::perspective(RADIANS(40), window->props.aspectRatio, 0.01f, 200.0f);

	carObst.push_back(posObstacol[carIndex[0]] + glm::vec3(0, 0.1, 0));
	carObst.push_back(posObstacol[carIndex[1]] + glm::vec3(0, 0.1, 0));
	carObst.push_back(posObstacolInv[carIndex[2]] + glm::vec3(0, 0.1, 0));
	carObst.push_back(posObstacolInv[carIndex[3]] + glm::vec3(0, 0.1, 0));
}	


Mesh* Tema2::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices)
{
	unsigned int VAO = 0;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	unsigned int VBO = 0;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
	
	unsigned int IBO = 0;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);
	// TODO(student): Create the IBO and bind it

	// TODO(student): Send indices data into the IBO buffer

	// ========================================================================
	// This section demonstrates how the GPU vertex shader program
	// receives data. It will be learned later, when GLSL shaders will be
	// introduced. For the moment, just think that each property value from
	// our vertex format needs to be sent to a certain channel, in order to
	// know how to receive it in the GLSL vertex shader.

	// Set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// Set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// Set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	// Set vertex color attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
	// ========================================================================

	// TODO(student): Unbind the VAO
	glBindVertexArray(0);
	// Check for OpenGL errors
	if (GetOpenGLError() == GL_INVALID_OPERATION)
	{
		cout << "\t[NOTE] : For students : DON'T PANIC! This error should go away when completing the tasks." << std::endl;
		cout << "\t[NOTE] : For developers : This happens because OpenGL core spec >=3.1 forbids null VAOs." << std::endl;
	}
	// Mesh information is saved into a Mesh object
	meshes[name] = new Mesh(name);
	meshes[name]->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));
	meshes[name]->vertices = vertices;
	meshes[name]->indices = indices;
	return meshes[name];
}


void Tema2::FrameStart()
{
	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0.68, 0.85, 0.9, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// Sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}


void Tema2::RenderScene()
{
	glm::mat4 modelMatrix = glm::mat4(1);
	//RenderSimpleMesh(meshes["iarba"], shaders["TemaShader"], modelMatrix); nu imi merge???
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -0.05, 0));
	RenderSimpleMesh(meshes["grass"], shaders["TemaShader"], modelMatrix);
		
	if (!isFp) {
		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition() + glm::vec3(0, 0.02, 0));
		modelMatrix *= tema_transform3D::RotateOY(rotateCar);
		modelMatrix = glm::scale(modelMatrix, glm::vec3(1.0f));
		RenderSimpleMesh(meshes["cube"], shaders["TemaShader"], modelMatrix);
	}
	modelMatrix = glm::mat4(1);
	RenderSimpleMesh(meshes["pista"], shaders["TemaShader"], modelMatrix);
	for (int i = 0; i < trees.size(); ++i) {
		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, trees[i] - glm::vec3(0,0.05,0));
		RenderSimpleMesh(meshes["tree"], shaders["TemaShader"], modelMatrix);
	}

	for (int i = 0; i < 2; ++i) {
		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, carObst[i]);
		modelMatrix *= tema_transform3D::RotateOY(atan2(directions[carIndex[i]].x, directions[carIndex[i]].z));
		RenderSimpleMesh(meshes["cube"], shaders["TemaShader"], modelMatrix);
	}
	for (int i = 2; i < 4; ++i) {
		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, carObst[i]);
		modelMatrix *= tema_transform3D::RotateOY(atan2(directionsInv[carIndex[i]].x, directionsInv[carIndex[i]].z));
		RenderSimpleMesh(meshes["cube"], shaders["TemaShader"], modelMatrix);
	}

}

void Tema2::RenderScene2()
{
	glm::mat4 modelMatrix = glm::mat4(1);
	//RenderSimpleMesh(meshes["iarba"], shaders["TemaShader"], modelMatrix);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -0.055, 0));
	RenderSimpleMesh(meshes["grass"], shaders["TemaShader"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition() - glm::vec3(0, 0.05, 0));
	modelMatrix *= tema_transform3D::RotateOY(rotateCar);
	modelMatrix = glm::scale(modelMatrix, glm::vec3(1.0f));
	RenderSimpleMesh(meshes["cube"], shaders["TemaShader"], modelMatrix);
	modelMatrix = glm::mat4(1);
	RenderSimpleMesh(meshes["pista"], shaders["TemaShader"], modelMatrix);
	for (int i = 0; i < trees.size(); ++i) {
		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, trees[i]);
		RenderSimpleMesh(meshes["tree"], shaders["TemaShader"], modelMatrix);
	}

	//modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 3.5f) + glm::vec3(0, 0.12, 0) + carPos);
	for (int i = 0; i < 2; ++i) {
		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, carObst[i]);
		modelMatrix *= tema_transform3D::RotateOY(atan2(directions[carIndex[i]].x, directions[carIndex[i]].z));
		RenderSimpleMesh(meshes["cube"], shaders["TemaShader"], modelMatrix);
	}

	for (int i = 2; i < 4; ++i) {
		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, carObst[i]);
		modelMatrix *= tema_transform3D::RotateOY(atan2(directionsInv[carIndex[i]].x, directionsInv[carIndex[i]].z));
		RenderSimpleMesh(meshes["cube"], shaders["TemaShader"], modelMatrix);
	}


}

void Tema2::Update(float deltaTimeSeconds) {
	for (int i = 0; i < 2; ++i) {
		if (i == 0) {
			carPos2[i] = glm::normalize(directions[carIndex[i]]) / 35.0f ;
			carPos[i] += glm::normalize(directions[carIndex[i]]) / 35.0f;
			//carPos2[i] = posObstacol[carIndex[i]];
		}
		else {
			carPos2[i] = glm::normalize(directions[carIndex[i]]) / 25.0f ;
			carPos[i] += glm::normalize(directions[carIndex[i]]) / 25.0f;

		}
		carObst[i] += carPos2[i];
		//carObst[i] = carPos2[i];
		if (glm::length(carPos[i]) >= glm::length(directions[carIndex[i]])) {
			carIndex[i]++;
			if (carIndex[i] == posObstacol.size()) carIndex[i] = 1;
			carPos[i] = glm::vec3(0, 0, 0);
		//	carObst[i] = posObstacol[carIndex[i]];

		}
	}
	
	for (int i = 2; i < 4; ++i) {
		if (i == 2) {
			carPos2[i] = glm::normalize(directionsInv[carIndex[i]]) / 25.0f;
			carPos[i] += glm::normalize(directionsInv[carIndex[i]]) / 25.0f;
		}
		else {
			carPos2[i] = glm::normalize(directionsInv[carIndex[i]]) / 25.0f;
			carPos[i] += glm::normalize(directionsInv[carIndex[i]]) / 25.0f;

		}


		if (glm::length(carPos[i]) >= glm::length(directionsInv[carIndex[i]])) {
			carIndex[i]++;
			if (carIndex[i] == posObstacolInv.size()-1) carIndex[i] = 0;
			carPos[i] = glm::vec3(0, 0, 0);
			//carObst[i] = posObstacolInv[carIndex[i]];
		} else 		carObst[i] += carPos2[i];

	}
	//carPos += glm::vec3(deltaTimeSeconds/100, 0, 0);
	cam = 1;
	glm::ivec2 resolution = window->GetResolution();
	glViewport(0, 0, resolution.x, resolution.y);
	projectionMatrix = glm::perspective(RADIANS(40), window->props.aspectRatio, 0.01f, 200.0f);
	RenderScene();

	if (isFp) {
		cam = 3;
		glClear(GL_DEPTH_BUFFER_BIT);
		glViewport(resolution.x / 2 - miniViewportArea2.width / 2, resolution.y - miniViewportArea2.height,
			miniViewportArea2.width, miniViewportArea2.height);
		projectionMatrix = glm::perspective(RADIANS(40), window->props.aspectRatio, 0.01f, 200.0f);

		RenderScene();
	}
	cam = 2;
	glClear(GL_DEPTH_BUFFER_BIT);
	glViewport(resolution.x - miniViewportArea.width + miniX, 0 + miniY, 
		miniViewportArea.width + miniWidth, miniViewportArea.height + miniHeight);
	projectionMatrix = glm::ortho(left, right, down, up, 0.01f, 200.0f);
	RenderScene2();	

}

void Tema2::FrameEnd()
{
	//DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}


void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// Render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// TODO(student): Get shader location for uniform mat4 "Model"
	int location = glGetUniformLocation(shader->program, "Model");

	// TODO(student): Set shader uniform "Model" to modelMatrix
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// TODO(student): Get shader location for uniform mat4 "View"
	int locationView = glGetUniformLocation(shader->program, "View");
	int locationProj = glGetUniformLocation(shader->program, "Projection");

	glm::mat4 viewMatrix;

	// TODO(student): Set shader uniform "View" to viewMatrix
	int locationCam = glGetUniformLocation(shader->program, "cam");

	if (cam == 1) {
			projectionMatrix = glm::perspective(RADIANS(40), window->props.aspectRatio, 0.01f, 200.0f);
		if (!isFp) {
			viewMatrix = camera->GetViewMatrix();
			glUniformMatrix4fv(locationView, 1, GL_FALSE, glm::value_ptr(viewMatrix));
			glUniformMatrix4fv(locationProj, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		}
		else {
			viewMatrix = cameraFp->GetViewMatrix();
			glUniformMatrix4fv(locationView, 1, GL_FALSE, glm::value_ptr(viewMatrix));
			glUniformMatrix4fv(locationProj, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		
		}
	}
	else if (cam == 2) {

		projectionMatrix = glm::ortho(left, right, down, up, 0.01f, 200.0f);
		viewMatrix = camera2->GetViewMatrix();
		glUniformMatrix4fv(locationView, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		glUniformMatrix4fv(locationProj, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		
	}
	else {
		if (cam == 3) {
			projectionMatrix = glm::perspective(RADIANS(40), window->props.aspectRatio, 0.01f, 200.0f);
			projectionMatrix = glm::scale(projectionMatrix, glm::vec3(-1, 1, 1));
			viewMatrix = cameraBack->GetViewMatrix();
			glUniformMatrix4fv(locationView, 1, GL_FALSE, glm::value_ptr(viewMatrix));
			glUniformMatrix4fv(locationProj, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		
		}
	}
	location = glGetUniformLocation(shader->program, "carPos");
	glUniform3fv(location, 1, glm::value_ptr(camera->GetTargetPosition()));
	
	//glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
	
	// TODO(student): Get shader location for uniform mat4 "Projection"
	// 
	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->m_VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);

}

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
	if (1)
	{
		float cameraSpeed = 2.0f;

		if (window->KeyHold(GLFW_KEY_W)) {
			// TODO(student): Translate the camera forward
			if (!intersectOtherCars()) {
				glm::vec3 newPos = camera->cameraPositionToCheck(cameraSpeed * deltaTime);
				bool canMove = false;
				for (int i = 0; i < triangles.size(); ++i) {
					if (isPointInTriangle(triangles[i], newPos)) {
						canMove = true;
						break;
					}
				}
				if (canMove == true) {
					camera->MoveForward(cameraSpeed * deltaTime);
					camera2->position = camera->GetTargetPosition() + glm::vec3(0, 10, 0);
					cameraPos = camera->position;
					cameraFp->position = camera->GetTargetPosition() - camera->forward * 0.60f + glm::vec3(0, 0.15, 0);
					cameraBack->position = camera->GetTargetPosition() + camera->forward * 0.60f + glm::vec3(0, 0.25, 0);
					//cameraBack->forward = -camera->forward;
				}
			}
		}

		if (window->KeyHold(GLFW_KEY_A)) {
			// TODO(student): Translate the camera to the left
			if (!intersectOtherCars()) {

				rotateCar += M_PI / 180;
				camera->RotateThirdPerson_OY(M_PI / 180);
				cameraFp->RotateFirstPerson_OY(M_PI / 180);
				cameraFp->position = camera->GetTargetPosition() - camera->forward * 0.60f + glm::vec3(0, 0.15, 0);
				cameraBack->RotateFirstPerson_OY(M_PI / 180);
				cameraBack->position = camera->GetTargetPosition() + camera->forward * 0.60f + glm::vec3(0, 0.25, 0);
				cameraPos = camera->position;
				
			}
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			// TODO(student): Translate the camera backward
			glm::vec3 newPos = camera->cameraPositionToCheck(-cameraSpeed * deltaTime);
			bool canMove = false;
			if (!intersectOtherCars()) {

				for (int i = 0; i < triangles.size(); ++i) {
					if (isPointInTriangle(triangles[i], newPos)) {
						canMove = true;
						break;
					}
				}
				if (canMove == true) {
					camera->MoveForward(-cameraSpeed * deltaTime);
					camera2->position = camera->GetTargetPosition() + glm::vec3(0, 10, 0);
					cameraFp->position = camera->GetTargetPosition() -camera->forward * 0.60f + glm::vec3(0, 0.15, 0);
					cameraPos = camera->position;
					cameraBack->position = camera->GetTargetPosition() + camera->forward * 0.60f + glm::vec3(0, 0.25, 0);
				}
			}
		}

		if (window->KeyHold(GLFW_KEY_D)) {
			// TODO(student): Translate the camera to the right
			//camera->TranslateRight(cameraSpeed * deltaTime);
			if (!intersectOtherCars()) {

				rotateCar -= M_PI / 180;
				camera->RotateThirdPerson_OY(-M_PI / 180);

				cameraFp->RotateFirstPerson_OY(-M_PI / 180);
				cameraFp->position = camera->GetTargetPosition() - camera->forward * 0.60f + glm::vec3(0, 0.15, 0);
				cameraBack->RotateFirstPerson_OY(-M_PI / 180);
				cameraBack->position = camera->GetTargetPosition() + camera->forward * 0.60f + glm::vec3(0, 0.25, 0);
				cameraPos = camera->position;
			}
		}

		if (window->KeyHold(GLFW_KEY_RIGHT)) {
			miniX +=  deltaTime*50;
		}
		if (window->KeyHold(GLFW_KEY_DOWN)) {
			miniY -=  deltaTime*50;
		}
		if (window->KeyHold(GLFW_KEY_UP)) {
			miniY +=  deltaTime*50;
		}
		if (window->KeyHold(GLFW_KEY_LEFT)) {
			miniX -=  deltaTime*50;
		}

		// redimensionare miniharta
		if (window->KeyHold(GLFW_KEY_O)) {
			miniX += deltaTime * 25;
			miniY += deltaTime * 25;
			miniWidth -= deltaTime * 50;
			miniHeight -= deltaTime * 50;
		}
		if (window->KeyHold(GLFW_KEY_P)) {
			miniX -= deltaTime * 25;
			miniY -= deltaTime * 25;
			miniWidth += deltaTime * 50;
			miniHeight += deltaTime * 50;
		}
	}

	if (1) {
		if (window->KeyHold(GLFW_KEY_I)) {
			up += deltaTime;
			down -= deltaTime;
			projectionMatrix = glm::ortho(left, right, down, up, 0.01f, 200.0f);
		}
		if (window->KeyHold(GLFW_KEY_K)) {

			up -= deltaTime;
			down += deltaTime;
			projectionMatrix = glm::ortho(left, right, down, up, 0.01f, 200.0f);
		}
		if (window->KeyHold(GLFW_KEY_J)) {
			right += deltaTime;
			left -= deltaTime;

			projectionMatrix = glm::ortho(left, right, down, up, 0.01f, 200.0f);
		}
		if (window->KeyHold(GLFW_KEY_L)) {

			right -= deltaTime;
			left += deltaTime;
			projectionMatrix = glm::ortho(left, right, down, up, 0.01f, 200.0f);
		}

	}
}


void Tema2::OnKeyPress(int key, int mods)
{
	// Add key press event
	if (key == GLFW_KEY_F) {
		isFp = !isFp;
	}
}


void Tema2::OnKeyRelease(int key, int mods)
{
	// Add key release event
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// Add mouse move event

	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float sensivityOX = 0.001f;
		float sensivityOY = 0.001f;

		if (window->GetSpecialKeyState() == 0) {
			camera->RotateFirstPerson_OX(-5 * deltaY * sensivityOX);
			camera->RotateFirstPerson_OY(-5 * deltaX * sensivityOY);
		}

		if (window->GetSpecialKeyState() & GLFW_MOD_CONTROL) {
			camera->RotateThirdPerson_OX(-5 * deltaY * sensivityOX);
			camera->RotateThirdPerson_OY(-5 * deltaX * sensivityOY);
		}
	}
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// Add mouse button press event
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// Add mouse button release event
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}

// distanta euclidiana
float Tema2::dist(float x1, float y1, float x2, float y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

// aria triunghi cand stim coordonatele celor 3 puncte
float Tema2::area(float x1, float y1, float x2, float y2, float x3, float y3) {
	float d1, d2, d3;
	d1 = dist(x1, y1, x2, y2);
	d2 = dist(x2, y2, x3, y3);
	d3 = dist(x1, y1, x3, y3);

	float s = (d1 + d2 + d3) / 2;

	return sqrt(s * (s - d1) * (s - d2) * (s - d3));
}

// functie care verifica daca un punct se afla in interioriul unui triunghi
bool Tema2::isPointInTriangle(TrianglePoints triangle, glm::vec3 point) {
	float arieTriunghi = area(triangle.p1.x, triangle.p1.z, triangle.p2.x, triangle.p2.z, triangle.p3.x, triangle.p3.z);
	float ariePct = area(triangle.p1.x, triangle.p1.z, triangle.p2.x, triangle.p2.z, point.x, point.z) +
		area(triangle.p1.x, triangle.p1.z, triangle.p3.x, triangle.p3.z, point.x, point.z) +
		area(triangle.p2.x, triangle.p2.z, triangle.p3.x, triangle.p3.z, point.x, point.z);
	return (arieTriunghi >= ariePct - arieTriunghi / 100) && (arieTriunghi <= ariePct + arieTriunghi / 100);
}

// functie care verifica daca 2 masini se intersecteaza, distanta sferica
bool Tema2::intersectionCubes(glm::vec3 a, glm::vec3 b) {

	float distCentr = dist(a.x, a.z, b.x, b.z);
	return distCentr <= razaMasini*2;
}

bool Tema2::intersectOtherCars() {
	glm::vec3 posss = camera->GetTargetPosition();
	return intersectionCubes(posss, carObst[0]) || intersectionCubes(posss, carObst[1])
		|| intersectionCubes(posss, carObst[2]) || intersectionCubes(posss, carObst[3]);
	//for (int i = 0; i < 4; ++i) {
		/*if (intersectionCubes(camera->GetTargetPosition(), carObst[i])) {
			cout << "TRUE";
			return true;
		}
		return false;
		*/

	//}
}