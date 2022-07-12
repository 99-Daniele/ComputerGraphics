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
	{"models/ceiling.obj", "textures/EOBSLM04.png"},
	{"models/doors.obj", "textures/EBBRD01.png"},
	{"models/door1.obj","textures/EOBDR02.png"},
	{"models/door2.obj","textures/EOBDR02.png"},
	{"models/door3.obj","textures/EOBDR02.png"},
	{"models/door4.obj","textures/EOBDR02.png"},
	{"models/door5.obj","textures/EOBDR02.png"},
	{"models/lever5.obj","textures/EOBDR02.png"},
	{"models/lever3.obj","textures/EOBDR02.png"},
	{"models/lever1.obj","textures/EOBDR02.png"},
	{"models/goldKeyHole4.obj","textures/EOBDR02.png"},
	{"models/copperKeyHole.obj","textures/EOBDR02.png"},
	{"models/floor.obj","textures/EOBSLM04.png"},
	{"models/goldKey.obj","textures/EOBSLM04.png"},
	{"models/copperKey.obj","textures/EOBSLM04.png"}
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


	std::vector<Model> ModelToLoad = { MCeiling,MDoors,MDoor1,MDoor2,MDoor3,MDoor4,MDoor5,MLever5,MLever3,MLever1,MGoldHole,MCopperHole,MFloor,MGoldKey,MCopperKey};
	std::vector<Texture> TextureToLoad = { TCeiling,TDoors,TDoor1,TDoor2,TDoor3,TDoor4,TDoor5,TLever5,TLever3,TLever1,TGoldHole,TCopperHole,TFloor,TGoldKey,TCopperKey };
	std::vector<DescriptorSet> DescriptorToLoad = { DSCeiling,DSDoors,DSDoor1,DSDoor2,DSDoor3,DSDoor4,DSDoor5,DSLever5,DSLever3,DSLever1,DSGoldHole,DSCopperHole,DSFloor,DSGoldKey,DSCopperKey };
	
	// Here you set the main application parameters
	void setWindowParameters() {
		// window size, titile and initial background
		windowWidth = 800;
		windowHeight = 600;
		windowTitle = "My Project";
		initialBackgroundColor = {1.0f, 1.0f, 1.0f, 1.0f};
		
		// Descriptor pool sizes
		uniformBlocksInPool = 15;
		texturesInPool = 15;
		setsInPool = 15;
	}
	
	void localInit() {
		DSL1.init(this, {
					{0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT},
					{1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT},
			});

		P1.init(this, "shaders/vert.spv", "shaders/frag.spv", { &DSL1 });

		for (int i = 0; i < 15; i++) {
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
		//DSCeiling.cleanup();
		//TCeiling.cleanup();
		//MCeiling.cleanup();
		for (int i = 0; i < 15; i++) {
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
				
		for (int i = 0; i < 15; i++) {
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

		const float ROT_SPEED = glm::radians(60.0f);
		const float MOVE_SPEED = 1.75f;

		static float debounce = time;
		
		glm::mat4 Prj = glm::mat4(1.0);
		static int prevCt = -1;
		Prj = glm::mat4(0.5, 0, 0, 0, 0, -0.666667, 0, 0, -0.1768, 0.235733, -0.0625, 0, 0, 0, 0.25, 1);

		// Updates unifoms for the objects
		glm::mat3 CamDir = glm::mat3(1.0f);
		glm::vec3 CamPos = glm::vec3(0.0f, 0.5f, 2.5f);
		glm::vec3 RobotPos = glm::vec3(3, 0, 2);
		glm::vec3 RobotCamDeltaPos = glm::vec3(0.0f, 0.335f, -0.0f);
		float lookYaw = 0.0;
		float lookPitch = 0.0;
		float lookRoll = 0.0;
					
		UniformBufferObject ubo{};

		//ubo.model = glm::rotate(glm::mat4(1.0f),
		//						time * glm::radians(90.0f),
		//						glm::vec3(0.0f, 0.0f, 1.0f));
		if (glfwGetKey(window, GLFW_KEY_LEFT)) {
			lookYaw += deltaT * ROT_SPEED;
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT)) {
			lookYaw -= deltaT * ROT_SPEED;
		}
		if (glfwGetKey(window, GLFW_KEY_UP)) {
			lookPitch += deltaT * ROT_SPEED;
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN)) {
			lookPitch -= deltaT * ROT_SPEED;
		}
		if (glfwGetKey(window, GLFW_KEY_Q)) {
			lookRoll -= deltaT * ROT_SPEED;
		}
		if (glfwGetKey(window, GLFW_KEY_E)) {
			lookRoll += deltaT * ROT_SPEED;
		}
		if (glfwGetKey(window, GLFW_KEY_A)) {
			RobotPos = RobotPos - MOVE_SPEED * glm::vec3(glm::rotate(glm::mat4(1.0f), lookYaw,
				glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(1, 0, 0, 1)) * deltaT;
		}
		if (glfwGetKey(window, GLFW_KEY_D)) {
			RobotPos = RobotPos + MOVE_SPEED * glm::vec3(glm::rotate(glm::mat4(1.0f), lookYaw,
				glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(1, 0, 0, 1)) * deltaT;
		}
		if (glfwGetKey(window, GLFW_KEY_W)) {
			RobotPos -= MOVE_SPEED * glm::vec3(glm::rotate(glm::mat4(1.0f), lookYaw,
				glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(0, 0, 1, 1)) * deltaT;
		}
		if (glfwGetKey(window, GLFW_KEY_S)) {
			RobotPos += MOVE_SPEED * glm::vec3(glm::rotate(glm::mat4(1.0f), lookYaw,
				glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(0, 0, 1, 1)) * deltaT;
		}


		glm::mat4 CamMat = glm::translate(glm::transpose(glm::mat4(CamDir)), -CamPos);

		glm::vec3 RRCDP = glm::vec3(glm::rotate(glm::mat4(1), lookYaw, glm::vec3(0, 1, 0)) *
			glm::vec4(RobotCamDeltaPos, 1.0f));


		CamMat = LookInDirMat(RobotPos+RRCDP, glm::vec3(lookYaw, lookPitch, lookRoll));
		//ubo.mMat = glm::scale(ubo.mMat, glm::vec3(SceneToLoad[j].scale));
		//ubo.mvpMat = Prj * CamMat * ubo.mMat;
		//ubo.nMat = glm::inverse(glm::transpose(ubo.mMat));


		ubo.view = CamMat;
		ubo.proj = glm::perspective(glm::radians(45.0f),
						swapChainExtent.width / (float) swapChainExtent.height,
						0.1f, 10.0f);
		ubo.proj[1][1] *= -1;
		
		void* data;

		// Here is where you actually update your uniforms
		for (int i = 0; i < 15; i++) {
			ubo.model = glm::mat4(1);
			vkMapMemory(device, DescriptorToLoad[i].uniformBuffersMemory[0][currentImage], 0,
				sizeof(ubo), 0, &data);
			memcpy(data, &ubo, sizeof(ubo));
			vkUnmapMemory(device, DescriptorToLoad[i].uniformBuffersMemory[0][currentImage]);
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