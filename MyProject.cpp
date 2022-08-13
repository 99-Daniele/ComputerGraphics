// This has been adapted from the Vulkan tutorial

#include "MyProject.hpp"
#include <vector>
#include <string>
#include <iostream>




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
	{"models/ceiling.obj", "textures/EOBRB01.png"},
	{"models/doors.obj", "textures/EBBRD01.png"},
	{"models/door1.obj","textures/EOBDR02.png"},
	{"models/door2.obj","textures/EOBDR02.png"},
	{"models/door3.obj","textures/EOBDR02.png"},
	{"models/door4.obj","textures/EOBDR02.png"},
	{"models/door5.obj","textures/EOBDR02.png"},
	{"models/lever5.obj","textures/SlotHandle.png"},
	{"models/lever3.obj","textures/SlotHandle.png"},
	{"models/lever1.obj","textures/SlotHandle.png"},
	{"models/goldKeyHole4.obj","textures/gold.jpg"},
	{"models/copperKeyHole.obj","textures/bronze.jpg"},
	{"models/floor.obj","textures/EOBSLM04.png"},
	{"models/goldKey.obj","textures/GoldKey.png"},
	{"models/copperKey.obj","textures/CopperKey.png"},
	{"models/walls.obj", "textures/EOBRB01.png"},
	{"models/winText.obj","textures/white.png"},
	{"models/keyText.obj","textures/white.png"},
	{"models/keyText1.obj","textures/white.png"},
	{"models/doorText1.obj","textures/white.png"},
	{"models/doorText2.obj","textures/white.png"},
	{"models/doorText3.obj","textures/white.png"},
	{"models/doorText4.obj","textures/white.png"},
	{"models/doorText5.obj","textures/white.png"},

};




std::vector<std::vector<std::string>> vettore = {
{"*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*"},
{"*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*"," "," ","*","*","*","*","*","*"},
{"*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*"," "," ","*","*","*","*","*","*"},
{"*","*","*","*","*","*","*","*","*","*","*","*"," "," "," ","*","*"," "," ","*","*","*","*","*"},
{"*","*","*","*","*","*","*","*","*","*","*","*"," ","*"," "," "," ","*"," ","*","*","*","*","*"},
{"*","*","*","*","*","*"," ","*","*","*","*","*"," ","*","*"," "," ","*"," "," ","*","*","*","*"},
{"*","*","*","*","*","*"," ","*","*","*"," "," "," "," "," ","*","*","*"," "," ","*","*","*","*"},
{"*","*","*","*","*","*"," ","*","*","*"," ","*","*","*"," ","*"," ","*"," ","*","*","*","*","*"},
{"*","*","*","*","*","*"," ","*","*"," "," ","*"," "," "," ","*"," ","*"," ","*","*","*","*","*"},
{"*","*","*","*","*","*"," "," "," "," "," "," ","*"," "," ","*"," "," "," ","*","*","*","*","*"},
{"*","*","*","*","*","*","*","*","*"," "," ","*","*"," ","*"," "," ","*"," ","*","*","*","*","*"},
{"*","*","*","*","*","*"," "," "," ","*","*"," ","*"," ","*"," "," ","*"," ","*","*","*","*","*"},
{"*","*","*","*"," "," "," "," "," "," "," "," "," "," ","*"," ","*"," "," "," ","*"," ","*","*"},
{"*","*","*","*"," ","*"," "," "," ","*","*"," ","*","*"," "," ","*","*"," ","*"," "," "," ","*"},
{"*","*","*","*"," ","*","*","*","*","*","*","*"," "," "," "," ","*"," "," "," ","*"," ","*","*"},
{"*","*"," "," "," "," "," "," "," "," "," "," "," ","*","*"," ","*"," "," "," ","*"," ","*","*"},
{"*","*"," ","*"," ","*","*","*","*","*","*","*","*","*","*"," "," ","*"," ","*"," "," ","*","*"},
{"*","*"," ","*"," "," "," "," "," "," "," "," "," "," "," ","*"," "," "," "," "," ","*","*","*"},
{"*","*"," ","*"," "," "," ","*","*","*"," "," "," ","*","*","*","*","*"," ","*","*","*","*","*"},
{"*","*"," ","*","*","*","*","*"," ","*"," ","*","*"," "," "," "," "," "," ","*","*","*","*","*"},
{"*"," "," "," ","*","*","*"," "," "," "," "," "," "," ","*","*","*","*","*","*","*","*","*","*"},
{"*"," "," "," "," "," "," "," ","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*"},
{"*"," "," "," ","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*"},
{"*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*","*"}
};

//PROBLEMI DA RISOLVERE
//NON RIESCO A IMPORTARE IL FILE MAP.TXT E FARE OPERAZIONI SU DI ESSA
//NON HO FATTO I SHADER
//POTREI TOGLIERE DEI TEXTURES 
//POTREI TOGLIERE MODELS DEI DIVERSI TESTI
//NON HO CAPITO BENE QUALE SEI L'INIZIO E SE CE UN BLOCCO CHE IN REALTA NON E' MURO



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

	Model MWinText;
	Texture TWinText;
	DescriptorSet DSWinText;

	Model MKeyText;
	Texture TKeyText;
	DescriptorSet DSKeyText;

	Model MKeyText1;
	Texture TKeyText1;
	DescriptorSet DSKeyText1;

	Model MDoorText1;
	Texture TDoorText1;
	DescriptorSet DSDoorText1;

	Model MDoorText2;
	Texture TDoorText2;
	DescriptorSet DSDoorText2;

	Model MDoorText3;
	Texture TDoorText3;
	DescriptorSet DSDoorText3;

	Model MDoorText4;
	Texture TDoorText4;
	DescriptorSet DSDoorText4;

	Model MDoorText5;
	Texture TDoorText5;
	DescriptorSet DSDoorText5;


	std::vector<Model> ModelToLoad = { MCeiling,MDoors,MDoor1,MDoor2,MDoor3,MDoor4,MDoor5,MLever5,MLever3,MLever1,MGoldHole,MCopperHole,MFloor,MGoldKey,MCopperKey,MWalls,MWinText,MKeyText,MKeyText1,MDoorText1,MDoorText2,MDoorText3,MDoorText4,MDoorText5 };
	std::vector<Texture> TextureToLoad = { TCeiling,TDoors,TDoor1,TDoor2,TDoor3,TDoor4,TDoor5,TLever5,TLever3,TLever1,TGoldHole,TCopperHole,TFloor,TGoldKey,TCopperKey,TWalls,TWinText,TKeyText,TKeyText1, TDoorText1,TDoorText2,TDoorText3,TDoorText4,TDoorText5 };
	std::vector<DescriptorSet> DescriptorToLoad = { DSCeiling,DSDoors,DSDoor1,DSDoor2,DSDoor3,DSDoor4,DSDoor5,DSLever5,DSLever3,DSLever1,DSGoldHole,DSCopperHole,DSFloor,DSGoldKey,DSCopperKey,DSWalls,DSWinText,DSKeyText,DSKeyText1,DSDoorText1,DSDoorText2,DSDoorText3,DSDoorText4,DSDoorText5 };

	// Here you set the main application parameters
	void setWindowParameters() {
		// window size, titile and initial background
		windowWidth = 800;
		windowHeight = 800;
		windowTitle = "My Project";
		initialBackgroundColor = { 0.0f, 0.0f, 0.0f, 0.0f };

		// Descriptor pool sizes
		uniformBlocksInPool = 24;
		texturesInPool = 24;
		setsInPool = 24;
	}

	void localInit() {
		DSL1.init(this, {
					{0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT},
					{1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT},
			});

		P1.init(this, "shaders/vert.spv", "shaders/frag.spv", { &DSL1 });

		for (int i = 0; i < 24; i++) {
			ModelToLoad[i].init(this, SceneToLoad[i].ObjFile);
			TextureToLoad[i].init(this, SceneToLoad[i].TextureFile);
			DescriptorToLoad[i].init(this, &DSL1, {
						{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
						{1, TEXTURE, 0, &TextureToLoad[i]}
				});
		}

		FILE *f;
		char vec[100];
		f = fopen("models/map.txt","r");
		while (fgets(vec, 100, f) != NULL)
		{
			printf("%s ", vec);
		}
	}

	// Here you destroy all the objects you created!		
	void localCleanup() {
		for (int i = 0; i < 24; i++) {
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

		for (int i = 0; i < 24; i++) {
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


	void checkSide(glm::vec4 *blockLimit, glm::vec4 *recentlyWalls, glm::vec2 *matrixCoo, int direction) {

		static glm::vec2 coo = *matrixCoo;
		static glm::vec4 limit = *blockLimit;
		static glm::vec4 recent = *recentlyWalls;
		float value;
		int column = 0;
		int row = 0;

		if (direction == 3 || direction == 1)
		{
			value = 0.1;
			if (direction == 3)
			{
				column = -1;
			}
			else {
				row = -1;
			}
		}
		else {
			value = -0.1;
			if (direction == 2)
			{
				column = 1;
			}
			else {
				row = 1;
			}
		}

		if (vettore[coo[1]+column][coo[0]+row] == "*")
		{
			if (recent[direction] == 0)
			{
				limit[direction] = limit[direction] + value;
				recent[direction] = 1;
			}
		}
		else {
			if (recent[direction] == 1)
			{
				printf("aumento di 0.2 su ");
				limit[direction] = limit[direction] - value;
				recent[direction] = 0;
			}
		}
		*recentlyWalls = recent;
		*blockLimit = limit;
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

		std::ifstream map("models/map.txt", std::ios::ate | std::ios::binary);
		if (!map.is_open()) {
			throw std::runtime_error("failed to open file!");
		}

		// Updates unifoms for the objects
		static glm::mat3 CamDir = glm::mat3(1.0f);
		static glm::vec3 CamPos = glm::vec3(0.0f, 0.5f, 2.5f);
		static glm::vec3 RobotPos = glm::vec3(1, 0, 3);
		glm::vec3 RobotCamDeltaPos = glm::vec3(0.0f, 0.335f, -0.0f);
		static float lookYaw = 0.0;
		static float lookPitch = 270.0;
		static float lookRoll = 0.0;
		static glm::vec4 blockLimit = glm::vec4(1.5, 0.5, 3.5, 2.5);
		static glm::vec4 recentlyWalls = glm::vec4(0, 0, 0, 0);
		static glm::vec2 matrixCoo = glm::vec2(7, 12);
		static glm::vec3 oldPos;

		oldPos = RobotPos;


		UniformBufferObject ubo{};

		if (glfwGetKey(window, GLFW_KEY_LEFT)) {
			lookPitch += deltaT * ROT_SPEED;
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT)) {
			lookPitch -= deltaT * ROT_SPEED;
		}
		if (glfwGetKey(window, GLFW_KEY_UP)) {
			lookYaw += deltaT * ROT_SPEED;
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


		static bool dCheck1 = false;
		static bool dCheck2 = false;
		static bool dCheck3 = false;
		static bool dCheck4 = false;
		static bool dCheck5 = false;
		static bool kCheck1 = false;
		static bool kCheck2 = false;

		if (blockLimit[0] < RobotPos[0])
		{
			matrixCoo[0]++;
			if (vettore[matrixCoo[1]][matrixCoo[0]] == "*" || blockLimit[0] == 3.5 && RobotPos.z <= 3.4 && RobotPos.z >= 2.6 && dCheck1 == false || blockLimit[0] == 6.5 && RobotPos.z <= 8.5 && RobotPos.z >= 7.6 && dCheck2 == false)
			{
				RobotPos = oldPos;
				matrixCoo[0]--;
			}
			else {
				printf("sto andando avanti ");
				blockLimit[1] = blockLimit[0];
				recentlyWalls[1] = 0;

				//controllo cosa fare se aventi ce muro 
				if (vettore[matrixCoo[1]][matrixCoo[0] + 1] == "*")
				{
					blockLimit[0] = blockLimit[0] + 0.9;
					recentlyWalls[0] = 1;
				}
				else {
					//l'if forse si può togliere considera blocco di dimensione minore di 1, considera caso muro dietro pero adesso vado al blocco davanti
					blockLimit[0]++;
				}

				printf("%f ", blockLimit[1]);
				printf("%f ", blockLimit[0]);

				checkSide(&blockLimit,&recentlyWalls,&matrixCoo,2);
				checkSide(&blockLimit, &recentlyWalls, &matrixCoo, 3);

				printf("%f ", blockLimit[3]);
				printf("%f \n", blockLimit[2]);
			}
		}


		if (blockLimit[1] > RobotPos[0])
		{
			matrixCoo[0]--;
			if (vettore[matrixCoo[1]][matrixCoo[0]] == "*" || blockLimit[0] == 4.5 && RobotPos.z <= 3.4 && RobotPos.z >= 2.6 && dCheck1 == false)
			{
				RobotPos = oldPos;
				matrixCoo[0]++;
			}
			else {
				//i need if old position already has a wall
				//if no and i have a wall minus 0.2 else same result
				//if yes and i have a wall same resut else plus 0.2
				//in this case olny for block 2 and 3 
				printf("sto andando dietro ");
				blockLimit[0] = blockLimit[1];
				recentlyWalls[0] = 0;

				if (vettore[matrixCoo[1]][matrixCoo[0] - 1] == "*")
				{
					blockLimit[1] = blockLimit[1] - 0.9;
					recentlyWalls[1] = 1;
				}
				else {
					blockLimit[1] --;
				}
				printf("%f ", blockLimit[1]);
				printf("%f ", blockLimit[0]);
				
				checkSide(&blockLimit, &recentlyWalls, &matrixCoo, 2);
				checkSide(&blockLimit, &recentlyWalls, &matrixCoo, 3);

				printf("%f ", blockLimit[3]);
				printf("%f \n", blockLimit[2]);
			}
		}



		//verso giu
		if (blockLimit[2] < RobotPos[2])
		{
			matrixCoo[1]++;
			if (vettore[matrixCoo[1]][matrixCoo[0]] == "*" || blockLimit[2] == -2.5 && RobotPos.x <= 4.5 && RobotPos.x >= 3.6 && dCheck5 == false || blockLimit[2] == 2.5 && RobotPos.x <= 9.5 && RobotPos.x >= 8.6 && dCheck3 == false || blockLimit[2] == 3.5 && RobotPos.x <= 12.5 && RobotPos.x >= 11.5 && dCheck4 == false)
			{
				RobotPos = oldPos;
				matrixCoo[1]--;
			}
			else {
				printf("sto andando giu ");
				blockLimit[3] = blockLimit[2];
				recentlyWalls[3] = 0;
				if (vettore[matrixCoo[1] + 1][matrixCoo[0]] == "*")
				{
					blockLimit[2] = blockLimit[2] + 0.9;
					recentlyWalls[2] = 1;
				}
				else {
					blockLimit[2] ++;
				}

				checkSide(&blockLimit, &recentlyWalls, &matrixCoo, 0);
				checkSide(&blockLimit, &recentlyWalls, &matrixCoo, 1);

				printf("%f ", blockLimit[1]);
				printf("%f ", blockLimit[0]);
				printf("%f ", blockLimit[3]);
				printf("%f \n", blockLimit[2]);
			}
		}


		//verso su
		if (blockLimit[3] > RobotPos[2])
		{
			matrixCoo[1]--;
			if (vettore[matrixCoo[1]][matrixCoo[0]] == "*" || blockLimit[3] == -1.5 && RobotPos.x <= 4.4 && RobotPos.x >= 3.5 && dCheck5 == false || blockLimit[3] == 3.5 && RobotPos.x <= 9.4 && RobotPos.x >= 8.5 && dCheck3 == false || blockLimit[3] == 4.5 && RobotPos.x <= 12.5 && RobotPos.x >= 11.5 && dCheck4 == false)
			{
				RobotPos = oldPos;
				matrixCoo[1]++;
			}
			else {
				printf("sto andando su ");
				blockLimit[2] = blockLimit[3];
				recentlyWalls[2] = 0;
				if (vettore[matrixCoo[1] - 1][matrixCoo[0]] == "*")
				{
					blockLimit[3] = blockLimit[3] - 0.9;
					recentlyWalls[3] = 1;
				}
				else {
					blockLimit[3] --;
				}

				checkSide(&blockLimit, &recentlyWalls, &matrixCoo, 0);
				checkSide(&blockLimit, &recentlyWalls, &matrixCoo, 1);

				printf("%f ", blockLimit[1]);
				printf("%f ", blockLimit[0]);
				printf("%f ", blockLimit[3]);
				printf("%f \n", blockLimit[2]);
			}
		}


		static glm::mat4 CamMat = glm::translate(glm::transpose(glm::mat4(CamDir)), -CamPos);
		glm::vec3 RRCDP = glm::vec3(glm::rotate(glm::mat4(1), lookPitch, glm::vec3(0, 1, 0)) *
			glm::vec4(RobotCamDeltaPos, 1.0f));
		CamMat = LookInDirMat(RobotPos + RRCDP, glm::vec3(lookYaw, lookPitch, lookRoll));

		ubo.view = CamMat;
		ubo.proj = glm::perspective(glm::radians(45.0f),
			swapChainExtent.width / (float)swapChainExtent.height,
			0.1f, 10.0f);
		ubo.proj[1][1] *= -1;

		void* data;
		static int var1 = 0;
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

		static glm::vec3 L1Pos = glm::vec3(0, 0, 0);
		static glm::vec3 L1Rot = glm::vec3(0.0, 0.0, 0.0);

		// Here is where you actually update your uniforms
		for (int i = 0; i < 24; i++) {
			ubo.model = glm::mat4(1);

			if (i == 2) {
				ubo.model = glm::translate(glm::mat4(1.0), D1Pos)*glm::translate(glm::mat4(1.0), glm::vec3(4, 0.0, 3))*
					glm::rotate(glm::mat4(1.0), glm::radians(D1Rot.y), glm::vec3(0, 1, 0)) *
					glm::rotate(glm::mat4(1.0), glm::radians(D1Rot.x), glm::vec3(1, 0, 0)) *
					glm::rotate(glm::mat4(1.0), glm::radians(D1Rot.z), glm::vec3(0, 0, 1))*glm::translate(glm::mat4(1.0), glm::vec3(-4, 0.0, -3));
			}
			if (i == 3) {
				ubo.model = glm::translate(glm::mat4(1.0), D2Pos)*glm::translate(glm::mat4(1.0), glm::vec3(7, 0.0, 8))*
					glm::rotate(glm::mat4(1.0), glm::radians(D2Rot.y), glm::vec3(0, 1, 0)) *
					glm::rotate(glm::mat4(1.0), glm::radians(D2Rot.x), glm::vec3(1, 0, 0)) *
					glm::rotate(glm::mat4(1.0), glm::radians(D2Rot.z), glm::vec3(0, 0, 1))*glm::translate(glm::mat4(1.0), glm::vec3(-7, 0.0, -8));
			}
			if (i == 4) {
				ubo.model = glm::translate(glm::mat4(1.0), D3Pos)*glm::translate(glm::mat4(1.0), glm::vec3(9, 0.0, 3))*
					glm::rotate(glm::mat4(1.0), glm::radians(D3Rot.y), glm::vec3(0, 1, 0)) *
					glm::rotate(glm::mat4(1.0), glm::radians(D3Rot.x), glm::vec3(1, 0, 0)) *
					glm::rotate(glm::mat4(1.0), glm::radians(D3Rot.z), glm::vec3(0, 0, 1))*glm::translate(glm::mat4(1.0), glm::vec3(-9, 0.0, -3));
			}
			if (i == 5) {
				ubo.model = glm::translate(glm::mat4(1.0), D4Pos)*glm::translate(glm::mat4(1.0), glm::vec3(12, 0.0, 4))*
					glm::rotate(glm::mat4(1.0), glm::radians(D4Rot.y), glm::vec3(0, 1, 0)) *
					glm::rotate(glm::mat4(1.0), glm::radians(D4Rot.x), glm::vec3(1, 0, 0)) *
					glm::rotate(glm::mat4(1.0), glm::radians(D4Rot.z), glm::vec3(0, 0, 1))*glm::translate(glm::mat4(1.0), glm::vec3(-12, 0.0, -4));
			}
			if (i == 6) {
				ubo.model = glm::translate(glm::mat4(1.0), D5Pos)*glm::translate(glm::mat4(1.0), glm::vec3(4, 0.0, -2))*
					glm::rotate(glm::mat4(1.0), glm::radians(D5Rot.y), glm::vec3(0, 1, 0)) *
					glm::rotate(glm::mat4(1.0), glm::radians(D5Rot.x), glm::vec3(1, 0, 0)) *
					glm::rotate(glm::mat4(1.0), glm::radians(D5Rot.z), glm::vec3(0, 0, 1))*glm::translate(glm::mat4(1.0), glm::vec3(-4, 0.0, 2));
			}
			if (i == 7) {
				ubo.model = glm::translate(glm::mat4(1.0), L5Pos)*
					glm::rotate(glm::mat4(1.0), glm::radians(L5Rot.y), glm::vec3(0, 1, 0)) *
					glm::rotate(glm::mat4(1.0), glm::radians(L5Rot.x), glm::vec3(1, 0, 0)) *
					glm::rotate(glm::mat4(1.0), glm::radians(L5Rot.z), glm::vec3(0, 0, 1))*glm::translate(glm::mat4(1.0), -L5Pos);
			}
			if (i == 8) {
				ubo.model = glm::translate(glm::mat4(1.0), L3Pos)*
					glm::rotate(glm::mat4(1.0), glm::radians(L3Rot.y), glm::vec3(0, 1, 0)) *
					glm::rotate(glm::mat4(1.0), glm::radians(L3Rot.x), glm::vec3(1, 0, 0)) *
					glm::rotate(glm::mat4(1.0), glm::radians(L3Rot.z), glm::vec3(0, 0, 1))*glm::translate(glm::mat4(1.0), -L3Pos);
			}
			if (i == 9) {
				ubo.model = glm::translate(glm::mat4(1.0), glm::vec3(L1Pos))*
					glm::rotate(glm::mat4(1.0), glm::radians(L1Rot.y), glm::vec3(0, 1, 0)) *
					glm::rotate(glm::mat4(1.0), glm::radians(L1Rot.x), glm::vec3(1, 0, 0)) *
					glm::rotate(glm::mat4(1.0), glm::radians(L1Rot.z), glm::vec3(0, 0, 1))* glm::translate(glm::mat4(1.0), glm::vec3(-L1Pos));
			}
			if (i == 13 || i == 17) {
				if (kCheck2) {
					ubo.model = glm::translate(glm::mat4(1.0), glm::vec3(0, 1, 0));
				}
			}
			if (i == 14 || i == 18) {
				if (kCheck1) {
					ubo.model = glm::translate(glm::mat4(1.0), glm::vec3(0, 1, 0));
				}
			}
			if (i == 19) {
				if (dCheck1) {
					ubo.model = glm::translate(glm::mat4(1.0), glm::vec3(0, 1, 0));
				}
			}
			if (i == 20) {
				if (dCheck3) {
					ubo.model = glm::translate(glm::mat4(1.0), glm::vec3(0, 1, 0));
				}
			}
			if (i == 23) {
				if (dCheck2) {
					ubo.model = glm::translate(glm::mat4(1.0), glm::vec3(0, 1, 0));
				}
			}
			if (i == 22) {
				if (dCheck4) {
					ubo.model = glm::translate(glm::mat4(1.0), glm::vec3(0, 1, 0));
				}
			}
			if (i == 21) {
				if (dCheck5) {
					ubo.model = glm::translate(glm::mat4(1.0), glm::vec3(0, 1, 0));
				}
			}

			vkMapMemory(device, DescriptorToLoad[i].uniformBuffersMemory[0][currentImage], 0,
				sizeof(ubo), 0, &data);
			memcpy(data, &ubo, sizeof(ubo));
			vkUnmapMemory(device, DescriptorToLoad[i].uniformBuffersMemory[0][currentImage]);
		}

		if (glfwGetKey(window, GLFW_KEY_K)) {
			printf("LOOK: %f\n", lookPitch);
			if (RobotPos.x > 1.5 && RobotPos.x < 2.5 && 2 < RobotPos.z && RobotPos.z < 2.5 && (lookPitch > 240.0 && lookPitch < 300.0)) {
				D1Pos = glm::vec3(-0.35, 0.0, 0.4);
				D1Rot.y = 90.0f;
				L1Pos = glm::vec3(2.5, 0.50, -2.2);
				L1Rot.z = 90.0f;
				dCheck1 = true;
			}
			if (RobotPos.x > 5.75 && RobotPos.x < 6.5 && 7.75 < RobotPos.z && RobotPos.z < 8.5 && kCheck1 == true && (lookPitch > 250.0 && lookPitch < 290.0)) {
				dCheck2 = true;
				D2Pos = glm::vec3(0.45, 0.0, 0.4);
				D2Rot.y = -90.0f;

			}
			if (RobotPos.x > 8.0 && RobotPos.x < 8.5 && 4.00 < RobotPos.z && RobotPos.z < 4.75 && ((lookPitch > 340.0 && lookPitch < 360.0) || (lookPitch > 0.0 && lookPitch < 20.0))) {
				D3Pos = glm::vec3(0.4, 0.0, -0.4);
				D3Rot.y = -90.0f;
				L3Rot.x = 0.0;
				dCheck3 = true;
			}
			if (RobotPos.x > 11.5 && RobotPos.x < 12.0 && 2.75 < RobotPos.z && RobotPos.z < 3.5 && kCheck2 == true && (lookPitch > 160.0 && lookPitch < 200.0)) {
				D4Pos = glm::vec3(0.4, 0.0, 0.35);
				D4Rot.y = -90.0f;
				dCheck4 = true;
			}
			if (RobotPos.x > 3.0 && RobotPos.x < 3.5 && -1.00 < RobotPos.z && RobotPos.z < -0.25 && ((lookPitch > 340.0 && lookPitch < 360.0) || (lookPitch > 0.0 && lookPitch < 20.0))) {
				D5Pos = glm::vec3(-0.4, 0.0, -0.35);
				D5Rot.y = -90.0f;
				L5Rot.x = 0.0;
				dCheck5 = true;
			}
		}

		if (glfwGetKey(window, GLFW_KEY_J)) {
			if (RobotPos.x > 14.5 && RobotPos.x < 15.5 && 2.5 < RobotPos.z && RobotPos.z < 3.5) {
				kCheck1 = true;
			}
			if (RobotPos.x > 9.5 && RobotPos.x < 10.5) {
				kCheck2 = true;
			}
		}
	}
};




// This is the main: probably you do not need to touch this!
int main() {
	MyProject app;

	try {
		app.run();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}