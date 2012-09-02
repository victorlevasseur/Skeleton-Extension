/*
Copyright (C) 2012 Victor Levasseur

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
  */

#include "GDL/ExtensionBase.h"
#include "GDL/Version.h"
#include "SkeletonObject.h"
#include <boost/version.hpp>

/**
 * This class declare information about the extension.
 */
class Extension : public ExtensionBase
{
    public:

        /**
         * Constructor of an extension declares everything the extension contains : Objects, actions, conditions and expressions.
         */
        Extension()
        {
            DECLARE_THE_EXTENSION("SkeletonObject",
                                  _("Objet Squelette"),
                                  _(L"Extension permettant de gérer les animations sous forme d'une squelette."),
                                  "Victor Levasseur",
                                  "zlib")


            //Declaration of all objects available
            DECLARE_OBJECT("Skeleton",
                           _("Squelette"),
                           _(L"Squelette déformable selon des animations."),
                           "res/Skeleton32.png",
                           &CreateSkeletonObject,
                           &DestroySkeletonObject,
                           "SkeletonObject");

                #if defined(GD_IDE_ONLY)

                objInfos.SetIncludeFile("SkeletonObject/SkeletonObject.h");

                /**
                Actions/Conditions for reading
                */

                DECLARE_OBJECT_ACTION("Play",
                               _("Jouer l'animation"),
                               _("Joue l'animation en cours."),
                               _("Jouer l'animation de _PARAM0_"),
                               _("Lecture"),
                               "res/actions/son24.png",
                               "res/actions/son.png");

                    instrInfo.AddParameter("object", _("Objet"), "Skeleton", false);

                    instrInfo.cppCallingInformation.SetFunctionName("Play").SetIncludeFile("SkeletonObject/SkeletonObject.h");

                DECLARE_END_OBJECT_ACTION()

                DECLARE_OBJECT_CONDITION("IsPlaying",
                               _("L'animation se joue"),
                               _("Teste si l'animation se joue."),
                               _("L'animation de _PARAM0_ se joue"),
                               _("Lecture"),
                               "res/actions/son24.png",
                               "res/actions/son.png");

                    instrInfo.AddParameter("object", _("Objet"), "Skeleton", false);

                    instrInfo.cppCallingInformation.SetFunctionName("IsPlaying").SetIncludeFile("SkeletonObject/SkeletonObject.h");

                DECLARE_END_OBJECT_CONDITION()

                DECLARE_OBJECT_ACTION("Pause",
                               _("Mettre en pause l'animation"),
                               _("Met en pause l'animation en cours."),
                               _("Mettre en pause l'animation de _PARAM0_"),
                               _("Lecture"),
                               "res/actions/son24.png",
                               "res/actions/son.png");

                    instrInfo.AddParameter("object", _("Objet"), "Skeleton", false);

                    instrInfo.cppCallingInformation.SetFunctionName("Pause").SetIncludeFile("SkeletonObject/SkeletonObject.h");

                DECLARE_END_OBJECT_ACTION()

                DECLARE_OBJECT_CONDITION("IsPausing",
                               _("L'animation est en pause"),
                               _("Teste si l'animation est en pause."),
                               _("L'animation de _PARAM0_ est en pause"),
                               _("Lecture"),
                               "res/actions/son24.png",
                               "res/actions/son.png");

                    instrInfo.AddParameter("object", _("Objet"), "Skeleton", false);

                    instrInfo.cppCallingInformation.SetFunctionName("IsPausing").SetIncludeFile("SkeletonObject/SkeletonObject.h");

                DECLARE_END_OBJECT_CONDITION()

                DECLARE_OBJECT_ACTION("Stop",
                               _("Arrêter l'animation"),
                               _("Arrête l'animation en cours."),
                               _("Arrêter l'animation de _PARAM0_"),
                               _("Lecture"),
                               "res/actions/son24.png",
                               "res/actions/son.png");

                    instrInfo.AddParameter("object", _("Objet"), "Skeleton", false);

                    instrInfo.cppCallingInformation.SetFunctionName("Stop").SetIncludeFile("SkeletonObject/SkeletonObject.h");

                DECLARE_END_OBJECT_ACTION()

                DECLARE_OBJECT_CONDITION("IsStopped",
                               _(L"L'animation est arrêtée"),
                               _(L"Teste si l'animation est arrêtée."),
                               _(L"L'animation de _PARAM0_ est arrêtée"),
                               _("Lecture"),
                               "res/actions/son24.png",
                               "res/actions/son.png");

                    instrInfo.AddParameter("object", _("Objet"), "Skeleton", false);

                    instrInfo.cppCallingInformation.SetFunctionName("IsStopped").SetIncludeFile("SkeletonObject/SkeletonObject.h");

                DECLARE_END_OBJECT_CONDITION()

                DECLARE_OBJECT_ACTION("SetSpeedRatio",
                               _("Changer la vitesse de l'animation"),
                               _(L"Change la vitesse de l'animation.\n1 = Vitesse normale, 1< = Ralentit, >1 = Accéléré"),
                               _(L"Mettre la vitesse de l'animation de _PARAM0_ à _PARAM2__PARAM1_"),
                               _("Lecture"),
                               "res/actions/son24.png",
                               "res/actions/son.png");

                    instrInfo.AddParameter("object", _("Objet"), "Skeleton", false);
                    instrInfo.AddParameter("expression", _("Valeur"), "", false);
                    instrInfo.AddParameter("operator", _("Signe de la modification"), "", false);

                    instrInfo.cppCallingInformation.SetFunctionName("SetSpeedRatio").SetManipulatedType("number").SetAssociatedGetter("GetSpeedRatio").SetIncludeFile("SkeletonObject/SkeletonObject.h");

                DECLARE_END_OBJECT_ACTION()

                DECLARE_OBJECT_CONDITION("TestSpeedRatio",
                               _("Tester la vitesse de l'animation"),
                               _("Teste la vitesse de l'animation."),
                               _("La vitesse de l'animation de _PARAM0_ est _PARAM2__PARAM1_"),
                               _("Lecture"),
                               "res/actions/son24.png",
                               "res/actions/son.png");

                    instrInfo.AddParameter("object", _("Objet"), "Skeleton", false);
                    instrInfo.AddParameter("expression", _("Valeur"), "", false);
                    instrInfo.AddParameter("relationalOperator", _("Signe de comparaison"), "", false);

                    instrInfo.cppCallingInformation.SetFunctionName("GetSpeedRatio").SetManipulatedType("number").SetIncludeFile("SkeletonObject/SkeletonObject.h");

                DECLARE_END_OBJECT_CONDITION()

                DECLARE_OBJECT_EXPRESSION("GetSpeedRatio", _("Vitesse de l'animation"), _("Vitesse de l'animation"), _("Lecture"), "res/actions/son.png")
                    instrInfo.AddParameter("object", _("Objet"), "Skeleton", false);

                    instrInfo.cppCallingInformation.SetFunctionName("GetSpeedRatio").SetIncludeFile("SkeletonObject/SkeletonObject.h");
                DECLARE_END_OBJECT_EXPRESSION()

                /**
                Actions/Conditions for seeking in animation
                */

                DECLARE_OBJECT_ACTION("Seek",
                               _(L"Aller à"),
                               _("Aller à une position précise (seconde) dans l'animation."),
                               _("Aller à _PARAM2__PARAM1_s dans l'animation de _PARAM0_"),
                               _("Lecture"),
                               "res/actions/son24.png",
                               "res/actions/son.png");

                    instrInfo.AddParameter("object", _("Objet"), "Skeleton", false);
                    instrInfo.AddParameter("expression", _("Valeur"), "", false);
                    instrInfo.AddParameter("operator", _("Signe de la modification"), "", false);

                    instrInfo.cppCallingInformation.SetFunctionName("Seek").SetManipulatedType("number").SetAssociatedGetter("GetPosition").SetIncludeFile("SkeletonObject/SkeletonObject.h");

                DECLARE_END_OBJECT_ACTION()

                DECLARE_OBJECT_CONDITION("TestPosition",
                               _("Position dans l'animation"),
                               _("Teste la position de lecture dans l'animation actuelle."),
                               _("La position dans l'animation est _PARAM2__PARAM1_ dans _PARAM0_"),
                               _("Lecture"),
                               "res/actions/son24.png",
                               "res/actions/son.png");

                    instrInfo.AddParameter("object", _("Objet"), "Skeleton", false);
                    instrInfo.AddParameter("expression", _("Valeur"), "", false);
                    instrInfo.AddParameter("relationalOperator", _("Signe de comparaison"), "", false);

                    instrInfo.cppCallingInformation.SetFunctionName("GetPosition").SetManipulatedType("number").SetIncludeFile("SkeletonObject/SkeletonObject.h");

                DECLARE_END_OBJECT_CONDITION()

                DECLARE_OBJECT_EXPRESSION("GetPosition", _("Position dans l'animation"), _("Position dans l'animation"), _("Lecture"), "res/actions/son.png")
                    instrInfo.AddParameter("object", _("Objet"), "Skeleton", false);

                    instrInfo.cppCallingInformation.SetFunctionName("GetPosition").SetIncludeFile("SkeletonObject/SkeletonObject.h");
                DECLARE_END_OBJECT_EXPRESSION()

                /**
                Actions/Conditions for changing animations
                */

                DECLARE_OBJECT_ACTION("SetAnimation",
                               _("Changer d'animation"),
                               _("Change l'animation en cours."),
                               _(L"Mettre l'animation _PARAM1_ à _PARAM0_"),
                               _("Animation"),
                               "res/actions/son24.png",
                               "res/actions/son.png");

                    instrInfo.AddParameter("object", _("Objet"), "Skeleton", false);
                    instrInfo.AddParameter("string", _("Nom"), "", false);

                    instrInfo.cppCallingInformation.SetFunctionName("SetAnimation").SetIncludeFile("SkeletonObject/SkeletonObject.h");

                DECLARE_END_OBJECT_ACTION()

                DECLARE_OBJECT_CONDITION("TestAnimation",
                               _("Tester le nom de l'animation qui se joue"),
                               _("Teste le nom de l'animation qui se joue."),
                               _("Le nom de l'animation de _PARAM0_ est _PARAM2__PARAM1_"),
                               _("Animation"),
                               "res/actions/son24.png",
                               "res/actions/son.png");

                    instrInfo.AddParameter("object", _("Objet"), "Skeleton", false);
                    instrInfo.AddParameter("string", _("Nom"), "", false);
                    instrInfo.AddParameter("relationalOperator", _("Signe de comparaison"), "", false);

                    instrInfo.cppCallingInformation.SetFunctionName("GetAnimation").SetManipulatedType("string").SetIncludeFile("SkeletonObject/SkeletonObject.h");

                DECLARE_END_OBJECT_CONDITION()

                DECLARE_OBJECT_STR_EXPRESSION("GetCurrentAnimation", _("Animation actuelle"), _("Animation actuelle"), _("Animation"), "res/actions/son.png")
                    instrInfo.AddParameter("object", _("Objet"), "Skeleton", false);

                    instrInfo.cppCallingInformation.SetFunctionName("GetAnimation").SetIncludeFile("SkeletonObject/SkeletonObject.h");
                DECLARE_END_OBJECT_STR_EXPRESSION()

                /**
                Actions/Conditions to dis/enable the animation system (in order to move manually bones)
                */

                DECLARE_OBJECT_ACTION("EnableAnimationSystem",
                               _(L"Dé/activer le système d'animation"),
                               _(L"Dé/active le système d'animation pour permettre par exemple de bouger manuellement les os."),
                               _(L"Activer le système d'animation de _PARAM0_ ? _PARAM1_"),
                               _(L"Fonctionnalités"),
                               "res/actions/son24.png",
                               "res/actions/son.png");

                    instrInfo.AddParameter("object", _("Objet"), "Skeleton", false);
                    instrInfo.AddParameter("yesorno", _("Activer ?"), "", false);

                    instrInfo.cppCallingInformation.SetFunctionName("EnableAnimationSystem").SetIncludeFile("SkeletonObject/SkeletonObject.h");

                DECLARE_END_OBJECT_ACTION()

                /**
                Actions/Conditions/Expressions to change (or get) bone's properties (angle, length, position)
                */

                DECLARE_OBJECT_ACTION("SetBoneAngle",
                               _(L"Changer l'angle d'un os"),
                               _(L"Change l'angle d'un os (relatif à l'os parent)."),
                               _(L"Mettre l'angle de l'os _PARAM1_ de _PARAM0_ à _PARAM3__PARAM2_"),
                               _("Os"),
                               "res/actions/son24.png",
                               "res/actions/son.png");

                    instrInfo.AddParameter("object", _("Objet"), "Skeleton", false);
                    instrInfo.AddParameter("string", _("Nom de l'os"), "", false);
                    instrInfo.AddParameter("expression", _("Angle"), "", false);
                    instrInfo.AddParameter("operator", _(L"Signe de l'opération"), "", false);

                    instrInfo.cppCallingInformation.SetFunctionName("SetBoneAngle").SetManipulatedType("number").SetAssociatedGetter("GetBoneAngle").SetIncludeFile("SkeletonObject/SkeletonObject.h");

                DECLARE_END_OBJECT_ACTION()

                DECLARE_OBJECT_CONDITION("TestBoneAngle",
                               _("Tester l'angle d'un os"),
                               _("Teste l'angle d'un os."),
                               _("L'angle (relatif) de _PARAM1_ de _PARAM0_ est _PARAM3__PARAM2_"),
                               _("Os"),
                               "res/actions/son24.png",
                               "res/actions/son.png");

                    instrInfo.AddParameter("object", _("Objet"), "Skeleton", false);
                    instrInfo.AddParameter("string", _("Nom de l'os"), "", false);
                    instrInfo.AddParameter("expression", _("Angle"), "", false);
                    instrInfo.AddParameter("relationalOperator", _("Signe de comparaison"), "", false);

                    instrInfo.cppCallingInformation.SetFunctionName("GetBoneAngle").SetManipulatedType("number").SetIncludeFile("SkeletonObject/SkeletonObject.h");

                DECLARE_END_OBJECT_CONDITION()

                DECLARE_OBJECT_EXPRESSION("GetBoneAngle", _("Angle d'un os"), _("Angle d'un os"), _("Os"), "res/actions/son.png")
                    instrInfo.AddParameter("object", _("Objet"), "Skeleton", false);
                    instrInfo.AddParameter("string", _("Nom de l'os"), "", false);

                    instrInfo.cppCallingInformation.SetFunctionName("GetBoneAngle").SetIncludeFile("SkeletonObject/SkeletonObject.h");
                DECLARE_END_OBJECT_EXPRESSION()

                DECLARE_OBJECT_EXPRESSION("GetBoneAbsoluteAngle", _("Angle absolut d'un os"), _("Angle absolut d'un os"), _("Os"), "res/actions/son.png")
                    instrInfo.AddParameter("object", _("Objet"), "Skeleton", false);
                    instrInfo.AddParameter("string", _("Nom de l'os"), "", false);

                    instrInfo.cppCallingInformation.SetFunctionName("GetBoneAbsoluteAngle").SetIncludeFile("SkeletonObject/SkeletonObject.h");
                DECLARE_END_OBJECT_EXPRESSION()



                DECLARE_OBJECT_ACTION("SetBoneLength",
                               _(L"Changer la longueur d'un os"),
                               _(L"Change la longueur d'un os."),
                               _(L"Mettre la longueur de l'os _PARAM1_ de _PARAM0_ à _PARAM3__PARAM2_"),
                               _("Os"),
                               "res/actions/son24.png",
                               "res/actions/son.png");

                    instrInfo.AddParameter("object", _("Objet"), "Skeleton", false);
                    instrInfo.AddParameter("string", _("Nom de l'os"), "", false);
                    instrInfo.AddParameter("expression", _("Longueur"), "", false);
                    instrInfo.AddParameter("operator", _(L"Signe de l'opération"), "", false);

                    instrInfo.cppCallingInformation.SetFunctionName("SetBoneLength").SetManipulatedType("number").SetAssociatedGetter("GetBoneLength").SetIncludeFile("SkeletonObject/SkeletonObject.h");

                DECLARE_END_OBJECT_ACTION()

                DECLARE_OBJECT_CONDITION("TestBoneLength",
                               _("Tester la longueur d'un os"),
                               _("Teste la longueur d'un os."),
                               _("La longueur de _PARAM1_ de _PARAM0_ est _PARAM3__PARAM2_"),
                               _("Os"),
                               "res/actions/son24.png",
                               "res/actions/son.png");

                    instrInfo.AddParameter("object", _("Objet"), "Skeleton", false);
                    instrInfo.AddParameter("string", _("Nom de l'os"), "", false);
                    instrInfo.AddParameter("expression", _("Longueur"), "", false);
                    instrInfo.AddParameter("relationalOperator", _("Signe de comparaison"), "", false);

                    instrInfo.cppCallingInformation.SetFunctionName("GetBoneLength").SetManipulatedType("number").SetIncludeFile("SkeletonObject/SkeletonObject.h");

                DECLARE_END_OBJECT_CONDITION()

                DECLARE_OBJECT_EXPRESSION("GetBoneLength", _("Longueur d'un os"), _("Longueur d'un os"), _("Os"), "res/actions/son.png")
                    instrInfo.AddParameter("object", _("Objet"), "Skeleton", false);
                    instrInfo.AddParameter("string", _("Nom de l'os"), "", false);

                    instrInfo.cppCallingInformation.SetFunctionName("GetBoneLength").SetIncludeFile("SkeletonObject/SkeletonObject.h");
                DECLARE_END_OBJECT_EXPRESSION()



                DECLARE_OBJECT_EXPRESSION("GetBoneCenterX", _("Position X du centre d'un os"), _("Position X du centre d'un os"), _("Os"), "res/actions/son.png")
                    instrInfo.AddParameter("object", _("Objet"), "Skeleton", false);
                    instrInfo.AddParameter("string", _("Nom de l'os"), "", false);

                    instrInfo.cppCallingInformation.SetFunctionName("GetBoneCenterX").SetIncludeFile("SkeletonObject/SkeletonObject.h");
                DECLARE_END_OBJECT_EXPRESSION()

                DECLARE_OBJECT_EXPRESSION("GetBoneCenterY", _("Position Y du centre d'un os"), _("Position Y du centre d'un os"), _("Os"), "res/actions/son.png")
                    instrInfo.AddParameter("object", _("Objet"), "Skeleton", false);
                    instrInfo.AddParameter("string", _("Nom de l'os"), "", false);

                    instrInfo.cppCallingInformation.SetFunctionName("GetBoneCenterY").SetIncludeFile("SkeletonObject/SkeletonObject.h");
                DECLARE_END_OBJECT_EXPRESSION()


            #endif
            DECLARE_END_OBJECT()

            CompleteCompilationInformation();
        };
        virtual ~Extension() {};

    protected:
    private:

        /**
         * This function is called by Game Develop so
         * as to complete information about how the extension was compiled ( which libs... )
         * -- Do not need to be modified. --
         */
        void CompleteCompilationInformation()
        {
            #if defined(GD_IDE_ONLY)
            compilationInfo.runtimeOnly = false;
            #else
            compilationInfo.runtimeOnly = true;
            #endif

            #if defined(__GNUC__)
            compilationInfo.gccMajorVersion = __GNUC__;
            compilationInfo.gccMinorVersion = __GNUC_MINOR__;
            compilationInfo.gccPatchLevel = /*__GNUC_PATCHLEVEL__*/1;
            #endif

            compilationInfo.boostVersion = BOOST_VERSION;

            compilationInfo.sfmlMajorVersion = 2;
            compilationInfo.sfmlMinorVersion = 0;

            #if defined(GD_IDE_ONLY)
            compilationInfo.wxWidgetsMajorVersion = wxMAJOR_VERSION;
            compilationInfo.wxWidgetsMinorVersion = wxMINOR_VERSION;
            compilationInfo.wxWidgetsReleaseNumber = wxRELEASE_NUMBER;
            compilationInfo.wxWidgetsSubReleaseNumber = wxSUBRELEASE_NUMBER;
            #endif

            compilationInfo.gdlVersion = RC_FILEVERSION_STRING;
            compilationInfo.sizeOfpInt = sizeof(int*);

            compilationInfo.informationCompleted = true;
        }
};

/**
 * Used by Game Develop to create the extension class
 * -- Do not need to be modified. --
 */
extern "C" ExtensionBase * GD_EXTENSION_API CreateGDExtension() {
    return new Extension;
}

/**
 * Used by Game Develop to destroy the extension class
 * -- Do not need to be modified. --
 */
extern "C" void GD_EXTENSION_API DestroyGDExtension(ExtensionBase * p) {
    delete p;
}
