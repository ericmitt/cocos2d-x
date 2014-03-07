/****************************************************************************
Copyright (c) 2013 cocos2d-x.org
Copyright (c) Microsoft Open Technologies, Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#pragma once

#include <d3d11_1.h>
#include <DirectXMath.h>
#include "DirectXHelper.h"
#include "CCGL.h"

// Helper class that initializes DirectX APIs for 3D rendering.
ref class DirectXBase abstract
{
internal:
    DirectXBase();

    virtual void Initialize();
    virtual void CreateDeviceResources();
    virtual void UpdateDevice(ID3D11Device1* device, ID3D11DeviceContext1* context, ID3D11RenderTargetView* renderTargetView);
    virtual void UpdateForWindowSizeChange(float width, float height);
    virtual void CreateWindowSizeDependentResources();
	virtual void OnOrientationChanged(Windows::Graphics::Display::DisplayOrientations orientation);

    virtual void CreateGLResources() = 0;

    void Render();

protected:

    // return true if eglSwapBuffers was called by OnRender
	virtual bool OnRender() = 0;
    virtual void OnUpdateDevice() = 0;
    bool InitializeAngle();
    void CloseAngle();

protected private:
    // Direct3D Objects.
    Microsoft::WRL::ComPtr<ID3D11Device1> m_d3dDevice;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext1> m_d3dContext;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_d3dRenderTargetView;
	D3D_FEATURE_LEVEL m_featureLevel;

    // Cached renderer properties.
    Windows::Foundation::Size m_renderTargetSize;
    Windows::Foundation::Rect m_windowBounds;
	Windows::Graphics::Display::DisplayOrientations m_orientation;

    // Angle EGL 
    bool m_bAngleInitialized;
	EGLDisplay m_eglDisplay;
	EGLContext m_eglContext;
	EGLSurface m_eglSurface;
	Microsoft::WRL::ComPtr<IWinrtEglWindow> m_eglWindow;
	Microsoft::WRL::ComPtr<IWinPhone8XamlD3DWindow> m_eglPhoneWindow;
    DirectX::XMMATRIX m_orientationMatrix;
    float m_aspectRatio;
};