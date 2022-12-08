//
// Created by Blurry on 9/9/2022.
//

//Obfuscate offset
#define OBFUSCATEOFFSET(str) string2Offset(OBFUSCATE(str))

//Library Target
#define targetLibName OBFUSCATE("libil2cpp.so")

//vars
float isLocalPlayerSize;

//-----------HOOKING------------//

void *(*get_transform)(void *component);
void (*Transform_set_localScale)(void *transform, Vector3);

void SetPlayerSize(void *transform, Vector3 scale)
{
    return Transform_set_localScale(get_transform(transform), scale);
}

void (*old_PlayerUpdateFunction)(void *instance);
void PlayerUpdateFunction(void *instance) {
    if (instance != NULL) {
        if(isLocalPlayerSize)
        {
            SetPlayerSize(instance, Vector3(isLocalPlayerSize, isLocalPlayerSize, isLocalPlayerSize));
        }
    }
    old_PlayerUpdateFunction(instance);
}

void Pointers() {
    get_transform = (void *(*)(void *)) getAbsoluteAddress(targetLibName, OBFUSCATEOFFSET("0x139A8A4"));
    Transform_set_localScale = (void (*)(void*, Vector3))getAbsoluteAddress(targetLibName, OBFUSCATEOFFSET("0x1310784"));
}
