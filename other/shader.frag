#version 330 core

out vec4 FragColor;
in vec3 ourColor;

in vec4 vertPos;

void main()
{
	// FragColor = vec4(ourColor, 1.0f);
	FragColor = vec4(vertPos.x+1.0f, vertPos.y+1.0f, vertPos.z+1.0f, vertPos.w+1.0f);
};