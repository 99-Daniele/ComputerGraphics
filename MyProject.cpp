// This has been adapted from the Vulkan tutorial

#include "MyProject.hpp"
#include <vector>

#include <string>

#include <iostream>


const std::string MODEL_PATH = "models/ceiling.obj";
const std::string TEXTURE_PATH = "textures/EOBSLM04.png";
//const std::string TEXTURE_PATH1 = "textures/Monet-Sunrise.png";

// The uniform buffer object used in this example
struct UniformBufferObject {
	alignas(16) glm::mat4 model;
	alignas(16) glm::mat4 view;
	alignas(16) glm::mat4 proj;
};

struct element {
	const char *ObjFile;
	const char *TextureFile;
};

const std::vector<element> SceneToLoad = {
	{"models/ceiling.obj", "textures/EOBFLT12.png"},
	{"models/doors.obj", "textures/EBBRD01.png"},
	{"models/door1.obj","textures/EOBDR02.png"},
	{"models/door2.obj","textures/EOBDR02.png"},
	{"models/door3.obj","textures/EOBDR02.png"},
	{"models/door4.obj","textures/EOBDR02.png"},
	{"models/door5.obj","textures/EOBDR02.png"},
	{"models/lever5.obj","textures/SlotHandle.png"},
	{"models/lever3.obj","textures/SlotHandle.png"},
	{"models/lever1.obj","textures/SlotHandle.png"},
	{"models/goldKeyHole4.obj","textures/GoldKey.png"},
	{"models/copperKeyHole.obj","textures/CopperKey.png"},
	{"models/floor.obj","textures/EOBSLM04.png"},
	{"models/goldKey.obj","textures/GoldKey.png"},
	{"models/copperKey.obj","textures/CopperKey.png"},
	{"models/walls.obj", "textures/EOBRB01.png"}
};


// MAIN ! 
class MyProject : public BaseProject {
	protected:
	// Here you list all the Vulkan objects you need:
	
	// Descriptor Layouts [what will be passed to the shaders]
	DescriptorSetLayout DSL1;

	// Pipelines [Shader couples]
	Pipeline P1;

	// Models, textures and Descriptors (values assigned to the uniforms)
	Model MCeiling;
	Texture TCeiling;
	DescriptorSet DSCeiling;

	Model MDoors;
	Texture TDoors;
	DescriptorSet DSDoors;

	Model MDoor1;
	Texture TDoor1;
	DescriptorSet DSDoor1;

	Model MDoor2;
	Texture TDoor2;
	DescriptorSet DSDoor2;

	Model MDoor3;
	Texture TDoor3;
	DescriptorSet DSDoor3;

	Model MDoor4;
	Texture TDoor4;
	DescriptorSet DSDoor4;

	Model MDoor5;
	Texture TDoor5;
	DescriptorSet DSDoor5;

	Model MLever5;
	Texture TLever5;
	DescriptorSet DSLever5;

	Model MLever3;
	Texture TLever3;
	DescriptorSet DSLever3;

	Model MLever1;
	Texture TLever1;
	DescriptorSet DSLever1;

	Model MGoldHole;
	Texture TGoldHole;
	DescriptorSet DSGoldHole;

	Model MCopperHole;
	Texture TCopperHole;
	DescriptorSet DSCopperHole;

	Model MFloor;
	Texture TFloor;
	DescriptorSet DSFloor;

	Model MGoldKey;
	Texture TGoldKey;
	DescriptorSet DSGoldKey;

	Model MCopperKey;
	Texture TCopperKey;
	DescriptorSet DSCopperKey;

	Model MWalls;
	Texture TWalls;
	DescriptorSet DSWalls;


	std::vector<Model> ModelToLoad = { MCeiling,MDoors,MDoor1,MDoor2,MDoor3,MDoor4,MDoor5,MLever5,MLever3,MLever1,MGoldHole,MCopperHole,MFloor,MGoldKey,MCopperKey,MWalls};
	std::vector<Texture> TextureToLoad = { TCeiling,TDoors,TDoor1,TDoor2,TDoor3,TDoor4,TDoor5,TLever5,TLever3,TLever1,TGoldHole,TCopperHole,TFloor,TGoldKey,TCopperKey,TWalls};
	std::vector<DescriptorSet> DescriptorToLoad = { DSCeiling,DSDoors,DSDoor1,DSDoor2,DSDoor3,DSDoor4,DSDoor5,DSLever5,DSLever3,DSLever1,DSGoldHole,DSCopperHole,DSFloor,DSGoldKey,DSCopperKey,DSWalls};
	
	// Here you set the main application parameters
	void setWindowParameters() {
		// window size, titile and initial background
		windowWidth = 800;
		windowHeight = 800;
		windowTitle = "My Project";
		initialBackgroundColor = {0.0f, 0.0f, 0.0f, 0.0f};
		
		// Descriptor pool sizes
		uniformBlocksInPool = 16;
		texturesInPool = 16;
		setsInPool = 16;
	}
	
	void localInit() {
		DSL1.init(this, {
					{0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT},
					{1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT},
			});

		P1.init(this, "shaders/vert.spv", "shaders/frag.spv", { &DSL1 });

		for (int i = 0; i < 16; i++) {
			ModelToLoad[i].init(this, SceneToLoad[i].ObjFile);
			TextureToLoad[i].init(this, SceneToLoad[i].TextureFile);
			DescriptorToLoad[i].init(this, &DSL1, {
						{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
						{1, TEXTURE, 0, &TextureToLoad[i]}
				});
		}
	}

	// Here you destroy all the objects you created!		
	void localCleanup() {
		for (int i = 0; i < 16; i++) {
			DescriptorToLoad[i].cleanup();
			ModelToLoad[i].cleanup();
			TextureToLoad[i].cleanup();
		}
		P1.cleanup();
		DSL1.cleanup();
	}
	
	// Here it is the creation of the command buffer:
	// You send to the GPU all the objects you want to draw,
	// with their buffers and textures
	void populateCommandBuffer(VkCommandBuffer commandBuffer, int currentImage) {
				
		vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
				P1.graphicsPipeline);
				
		for (int i = 0; i < 16; i++) {
			VkBuffer vertexBuffers[] = { ModelToLoad[i].vertexBuffer };
			VkDeviceSize offsets[] = { 0 };
			vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
			vkCmdBindIndexBuffer(commandBuffer, ModelToLoad[i].indexBuffer, 0,
				VK_INDEX_TYPE_UINT32);
			vkCmdBindDescriptorSets(commandBuffer,
				VK_PIPELINE_BIND_POINT_GRAPHICS,
				P1.pipelineLayout, 0, 1, &DescriptorToLoad[i].descriptorSets[currentImage],
				0, nullptr);
			vkCmdDrawIndexed(commandBuffer,
				static_cast<uint32_t>(ModelToLoad[i].indices.size()), 1, 0, 0, 0);
		}
	}

	glm::mat4 LookInDirMat(glm::vec3 Pos, glm::vec3 Angs) {
		glm::mat4 out = glm::rotate(glm::mat4(1.0), glm::radians(-Angs.z), glm::vec3(0, 0, 1))*glm::rotate(glm::mat4(1.0), glm::radians(-Angs.x), glm::vec3(1, 0, 0))*
			glm::rotate(glm::mat4(1.0), glm::radians(-Angs.y), glm::vec3(0, 1, 0))*translate(glm::mat4(1.0), glm::vec3(-Pos.x, -Pos.y, -Pos.z));
		return out;
	}


	// Here is where you update the uniforms.
	// Very likely this will be where you will be writing the logic of your application.
	void updateUniformBuffer(uint32_t currentImage) {
		static auto startTime = std::chrono::high_resolution_clock::now();
		static float lastTime = 0.0f;
		auto currentTime = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration<float, std::chrono::seconds::period>
					(currentTime - startTime).count();
		float deltaT = time - lastTime;
		lastTime = time;

		const float ROT_SPEED = glm::radians(3000.0f);
		const float MOVE_SPEED = 1.75f;

		static float debounce = time;
		
		glm::mat4 Prj = glm::mat4(1.0);
		static int prevCt = -1;
		Prj = glm::mat4(0.5, 0, 0, 0, 0, -0.666667, 0, 0, -0.1768, 0.235733, -0.0625, 0, 0, 0, 0.25, 1);

		// Updates unifoms for the objects
		static glm::mat3 CamDir = glm::mat3(1.0f);
		static glm::vec3 CamPos = glm::vec3(0.0f, 0.5f, 2.5f);
		static glm::vec3 RobotPos = glm::vec3(1, 0, 3);
		glm::vec3 RobotCamDeltaPos = glm::vec3(0.0f, 0.335f, -0.0f);
		static float lookYaw = 0.0;
		static float lookPitch = 270.0;
		static float lookRoll = 0.0;
					
		UniformBufferObject ubo{};

		if (glfwGetKey(window, GLFW_KEY_LEFT)) {
			lookPitch += deltaT * ROT_SPEED;
			if (lookPitch < 0.0)
				lookPitch += 360.0;
			else if (lookPitch > 360.0)
				lookPitch -= 360.0;
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT)) {
			lookPitch -= deltaT * ROT_SPEED;
			if (lookPitch < 0.0)
				lookPitch += 360.0;
			else if (lookPitch > 360.0)
				lookPitch -= 360.0;
		}
		if (glfwGetKey(window, GLFW_KEY_UP)) {
			lookYaw += deltaT * ROT_SPEED;
			if (lookYaw < 0.0)
				lookYaw += 360.0;
			else if (lookYaw > 360.0)
				lookYaw -= 360.0;
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN)) {
			lookYaw -= deltaT * ROT_SPEED;
			if (lookYaw < 0.0)
				lookYaw += 360.0;
			else if (lookYaw > 360.0)
				lookYaw -= 360.0;
		}
		if (glfwGetKey(window, GLFW_KEY_Q)) {
			lookRoll -= deltaT * ROT_SPEED;
			if (lookRoll < 0.0)
				lookRoll += 360.0;
			else if (lookRoll > 360.0)
				lookRoll -= 360.0;
		}
		if (glfwGetKey(window, GLFW_KEY_E)) {
			lookRoll += deltaT * ROT_SPEED;
			if (lookRoll < 0.0)
				lookRoll += 360.0;
			else if (lookRoll > 360.0)
				lookRoll -= 360.0;
		}
		if (glfwGetKey(window, GLFW_KEY_A)) {
			RobotPos -= MOVE_SPEED * glm::vec3(glm::rotate(glm::mat4(1.0f), glm::radians(lookPitch),
				glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(1, 0, 0, 1)) * deltaT;
		}
		if (glfwGetKey(window, GLFW_KEY_D)) {
			RobotPos += MOVE_SPEED * glm::vec3(glm::rotate(glm::mat4(1.0f), glm::radians(lookPitch),
				glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(1, 0, 0, 1)) * deltaT;
		}
		if (glfwGetKey(window, GLFW_KEY_W)) {
			RobotPos -= MOVE_SPEED * glm::vec3(glm::rotate(glm::mat4(1.0f), glm::radians(lookPitch),
				glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(0, 0, 1, 1)) * deltaT;
		}
		if (glfwGetKey(window, GLFW_KEY_S)) {
			RobotPos += MOVE_SPEED * glm::vec3(glm::rotate(glm::mat4(1.0f), glm::radians(lookPitch),
				glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(0, 0, 1, 1)) * deltaT;
		}


		static glm::mat4 CamMat = glm::translate(glm::transpose(glm::mat4(CamDir)), -CamPos);
		glm::vec3 RRCDP = glm::vec3(glm::rotate(glm::mat4(1), lookPitch, glm::vec3(0, 1, 0)) *
			glm::vec4(RobotCamDeltaPos, 1.0f));
		CamMat = LookInDirMat(RobotPos+RRCDP, glm::vec3(lookYaw, lookPitch, lookRoll));



		ubo.view = CamMat;
		ubo.proj = glm::perspective(glm::radians(45.0f),
						swapChainExtent.width / (float) swapChainExtent.height,
						0.1f, 10.0f);
		ubo.proj[1][1] *= -1;
		
		void* data;

		static glm::vec3 D1Pos = glm::vec3(0.0, 0.0, 0.0);
		static glm::vec3 D1Rot = glm::vec3(0.0, 0.0, 0.0);

		static glm::vec3 D2Pos = glm::vec3(0.0, 0.0, 0.0);
		static glm::vec3 D2Rot = glm::vec3(0.0, 0.0, 0.0);

		static glm::vec3 D3Pos = glm::vec3(0.0, 0.0, 0.0);
		static glm::vec3 D3Rot = glm::vec3(0.0, 0.0, 0.0);

		static glm::vec3 D4Pos = glm::vec3(0.0, 0.0, 0.0);
		static glm::vec3 D4Rot = glm::vec3(0.0, 0.0, 0.0);

		static glm::vec3 D5Pos = glm::vec3(0.0, 0.0, 0.0);
		static glm::vec3 D5Rot = glm::vec3(0.0, 0.0, 0.0);


		static glm::vec3 L5Pos = glm::vec3(3.3, 0.5, -1.5);
		static glm::vec3 L5Rot = glm::vec3(70.0, 0.0, 0.0);

		static glm::vec3 L3Pos = glm::vec3(8.3, 0.50, 3.5);
		static glm::vec3 L3Rot = glm::vec3(70.0, 0.0, 0.0);

		static glm::vec3 L1Pos = glm::vec3(4.2, 1.25, 3.4);
		static glm::vec3 L1Rot = glm::vec3(0.0, -180.0, 70.0);

		

		// Here is where you actually update your uniforms
		for (int i = 0; i < 16; i++) {
			ubo.model = glm::mat4(1);
			//door1 translate(0.35,-0.4,0)*rotation(lungo z di +90)
			if (i==2) {
				ubo.model = glm::translate(glm::mat4(1.0), D1Pos)*glm::translate(glm::mat4(1.0), glm::vec3(4, 0.0, 3))*
					glm::rotate(glm::mat4(1.0), glm::radians(D1Rot.y), glm::vec3(0, 1, 0)) *
					glm::rotate(glm::mat4(1.0), glm::radians(D1Rot.x), glm::vec3(1, 0, 0)) *
					glm::rotate(glm::mat4(1.0), glm::radians(D1Rot.z), glm::vec3(0, 0, 1))*glm::translate(glm::mat4(1.0), glm::vec3(-4, 0.0, -3));
			}
			//door2 translate(0.45,-0.4,0)*rotation(lungo z di +90)
			if (i == 3) {
				ubo.model = glm::translate(glm::mat4(1.0), D2Pos)*glm::translate(glm::mat4(1.0), glm::vec3(7, 0.0, 8))*
					glm::rotate(glm::mat4(1.0), glm::radians(D2Rot.y), glm::vec3(0, 1, 0)) *
					glm::rotate(glm::mat4(1.0), glm::radians(D2Rot.x), glm::vec3(1, 0, 0)) *
					glm::rotate(glm::mat4(1.0), glm::radians(D2Rot.z), glm::vec3(0, 0, 1))*glm::translate(glm::mat4(1.0), glm::vec3(-7, 0.0, -8));
			}
			//door3 translation(0.4,0.4,0)*rotation(lungo z di -90)
			if (i == 4) {
				ubo.model = glm::translate(glm::mat4(1.0), D3Pos)*glm::translate(glm::mat4(1.0), glm::vec3(9, 0.0, 3))*
					glm::rotate(glm::mat4(1.0), glm::radians(D3Rot.y), glm::vec3(0, 1, 0)) *
					glm::rotate(glm::mat4(1.0), glm::radians(D3Rot.x), glm::vec3(1, 0, 0)) *
					glm::rotate(glm::mat4(1.0), glm::radians(D3Rot.z), glm::vec3(0, 0, 1))*glm::translate(glm::mat4(1.0), glm::vec3(-9, 0.0, -3));
			}
			//door4 translation(0.4,-0.35,0)*rotation(lungo z di -90)
			if (i == 5) {
				ubo.model = glm::translate(glm::mat4(1.0), D4Pos)*glm::translate(glm::mat4(1.0), glm::vec3(12, 0.0, 4))*
					glm::rotate(glm::mat4(1.0), glm::radians(D4Rot.y), glm::vec3(0, 1, 0)) *
					glm::rotate(glm::mat4(1.0), glm::radians(D4Rot.x), glm::vec3(1, 0, 0)) *
					glm::rotate(glm::mat4(1.0), glm::radians(D4Rot.z), glm::vec3(0, 0, 1))*glm::translate(glm::mat4(1.0), glm::vec3(-12, 0.0, -4));
			}
			//door5 translation(-0.4,0.35,0)*rotation(lungo z di -90)
			if (i == 6) {
				ubo.model = glm::translate(glm::mat4(1.0), D5Pos)*glm::translate(glm::mat4(1.0), glm::vec3(4, 0.0, -2))*
					glm::rotate(glm::mat4(1.0), glm::radians(D5Rot.y), glm::vec3(0, 1, 0)) *
					glm::rotate(glm::mat4(1.0), glm::radians(D5Rot.x), glm::vec3(1, 0, 0)) *
					glm::rotate(glm::mat4(1.0), glm::radians(D5Rot.z), glm::vec3(0, 0, 1))*glm::translate(glm::mat4(1.0), glm::vec3(-4, 0.0, 2));
			}
			//lever5 rotation(asse x di +70)
			if (i == 7) {
				ubo.model = glm::translate(glm::mat4(1.0), L5Pos)*
					glm::rotate(glm::mat4(1.0), glm::radians(L5Rot.y), glm::vec3(0, 1, 0)) *
					glm::rotate(glm::mat4(1.0), glm::radians(L5Rot.x), glm::vec3(1, 0, 0)) *
					glm::rotate(glm::mat4(1.0), glm::radians(L5Rot.z), glm::vec3(0, 0, 1))*glm::translate(glm::mat4(1.0), -L5Pos);
			}
			//lever3 rotation(asse x di +70)
			if (i == 8) {
				ubo.model = glm::translate(glm::mat4(1.0), L3Pos)*
					glm::rotate(glm::mat4(1.0), glm::radians(L3Rot.y), glm::vec3(0, 1, 0)) *
					glm::rotate(glm::mat4(1.0), glm::radians(L3Rot.x), glm::vec3(1, 0, 0)) *
					glm::rotate(glm::mat4(1.0), glm::radians(L3Rot.z), glm::vec3(0, 0, 1))*glm::translate(glm::mat4(1.0), -L3Pos);
			}
			//lever1 rotation(asse x di +70)
			if (i == 9) {
				ubo.model = glm::translate(glm::mat4(1.0), L1Pos) *
					glm::rotate(glm::mat4(1.0), glm::radians(L1Rot.y), glm::vec3(0, 1, 0)) *
					glm::rotate(glm::mat4(1.0), glm::radians(L1Rot.x), glm::vec3(1, 0, 0)) *
					glm::rotate(glm::mat4(1.0), glm::radians(L1Rot.z), glm::vec3(0, 0, 1)) * glm::translate(glm::mat4(1.0), glm::vec3(-3.3, -0.5, -2.5));
			}
			
			vkMapMemory(device, DescriptorToLoad[i].uniformBuffersMemory[0][currentImage], 0, sizeof(ubo), 0, &data);
			memcpy(data, &ubo, sizeof(ubo));
			vkUnmapMemory(device, DescriptorToLoad[i].uniformBuffersMemory[0][currentImage]);
		}

		//door1 translate(0.35,-0.4,0)*rotation(lungo z di -90)
		if (glfwGetKey(window, GLFW_KEY_K)) {
			printf("LOOK: %f\n", lookPitch);
			if ( RobotPos.x > 5.0 && RobotPos.x < 5.5 && 3.5 < RobotPos.z && RobotPos.z < 4.0 && (lookPitch > 70.0 && lookPitch < 110.0)) {
				D1Pos = glm::vec3(-0.35, 0.0, 0.4);
				D1Rot.y = 90.0f;
				L1Pos = glm::vec3(3.75, 0.5, 3.4);
				L1Rot.z = 0.0f;
			}
			if (RobotPos.x > 5.75 && RobotPos.x < 6.5 && 7.75 < RobotPos.z && RobotPos.z < 8.5 && (lookPitch > 250.0 && lookPitch < 290.0)) {
				D2Pos = glm::vec3(0.45, 0.0, 0.4);
				D2Rot.y = -90.0f;
			}
			if (RobotPos.x > 8.0 && RobotPos.x < 8.5 && 4.00 < RobotPos.z && RobotPos.z < 4.75 && ((lookPitch > 340.0 && lookPitch < 360.0) || (lookPitch > 0.0 && lookPitch < 20.0))) {
				D3Pos = glm::vec3(0.4, 0.0, -0.4);
				D3Rot.y = -90.0f;
				L3Rot.x = 0.0;
			}
			if (RobotPos.x > 11.5 && RobotPos.x < 12.0 && 2.75 < RobotPos.z && RobotPos.z < 3.5 && (lookPitch > 160.0 && lookPitch < 200.0)) {
				D4Pos = glm::vec3(0.4, 0.0, 0.35);
				D4Rot.y = -90.0f;
			}
			if (RobotPos.x > 3.0 && RobotPos.x < 3.5 && -1.00 < RobotPos.z && RobotPos.z < -0.25 && ((lookPitch > 340.0 && lookPitch < 360.0) || (lookPitch > 0.0 && lookPitch < 20.0))) {
				D5Pos = glm::vec3(-0.4, 0.0, -0.35);
				D5Rot.y = -90.0f;
				L5Rot.x = 0.0;
			}
		}
	}	
};

// This is the main: probably you do not need to touch this!
int main() {
    MyProject app;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}