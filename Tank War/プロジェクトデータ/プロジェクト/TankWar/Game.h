//
// Game.h
//

#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"
#include "MyLib/SceneManager.h"
#include "UserResources.h"
#include "RenderTexture.h"
#include "MyLib/TransitionMask.h"
#include "MyLib/SoundManager.h"


// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game final : public DX::IDeviceNotify
{
public:

    Game() noexcept(false);
    ~Game() = default;

    Game(Game&&) = default;
    Game& operator= (Game&&) = default;

    Game(Game const&) = delete;
    Game& operator= (Game const&) = delete;

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // IDeviceNotify
    void OnDeviceLost() override;
    void OnDeviceRestored() override;

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowMoved();
    void OnDisplayChange();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const noexcept;


private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();

    // Device resources.
    std::unique_ptr<DX::DeviceResources>    m_deviceResources;

    // Rendering loop timer.
    DX::StepTimer                           m_timer;

private:
    // 画面モード（true : フルスクリーン）
    BOOL m_fullscreen;

    // キーボードステートトラッカー
    DirectX::Keyboard::KeyboardStateTracker m_keyboardTracker;

    // マウスステートトラッカー
    DirectX::Mouse::ButtonStateTracker m_mouseTracker;

    // 共通ステートへのポインタ
    std::unique_ptr<DirectX::CommonStates> m_states;

    // ユーザーリソースへのポインタ
    std::unique_ptr<UserResources> m_userResources;

    // シーンマネージャーへのポインタ
    std::unique_ptr<SceneManager<UserResources>> m_sceneManager;

    // レンダリングテクスチャ
    std::unique_ptr<DX::RenderTexture> m_transitionTexture;

    // 画面遷移マスク
    std::unique_ptr<TransitionMask> m_transitionMask;

    // サウンドマネージャー
    std::unique_ptr<SoundManager> m_soundManager;

    // オーディオエンジン
    std::unique_ptr<DirectX::AudioEngine> m_audioEngine;
};
