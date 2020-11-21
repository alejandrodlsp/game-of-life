#version 330 core

out vec4 FragColor;
in vec2 oTexPos;

uniform sampler2D uTexture;
uniform float uBorderWidth;
uniform int uTableWidth;
uniform int uTableHeight;

float mod(float x, float y)
{
  return x - y * floor(x/y);
}

void main()
{
	float perx = mod(oTexPos.x, 1.0 / uTableWidth);
	float pery = mod(oTexPos.y, 1.0 / uTableHeight);
    if( perx < uBorderWidth || perx > 1 - uBorderWidth){
        FragColor = vec4(0.3, 0.3, 0.3, 1.0);
    }
	else if( pery < uBorderWidth || pery > 1 - uBorderWidth){
        FragColor = vec4(0.3, 0.3, 0.3, 1.0);
    }
    else {
        FragColor = texture(uTexture, oTexPos);   
    }
}