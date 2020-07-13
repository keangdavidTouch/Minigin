#include "MiniginPCH.h"
#include "GameObject.h"
#include "BaseComponent.h"
#include "ColliderManager.h"

kd::GameObject::GameObject(const std::string& tag)
	: m_Parent(nullptr)
	, m_Scene(nullptr)
	, m_Tag(tag)
	, m_Childs(std::vector<GameObject*>())
	, m_Components(std::vector<BaseComponent*>())
{
}

kd::GameObject::~GameObject()
{
	for (BaseComponent* component : m_Components)
	{
		SafeDelete(component);
	}

	for(GameObject* child: m_Childs)
	{
		SafeDelete(child);
	}
}

void kd::GameObject::AddChild(GameObject* child)
{
	auto it = std::find(m_Childs.begin(), m_Childs.end(), child);
	if (it == m_Childs.end())
	{
		child->m_Parent = this;
		child->Initalize();
		m_Childs.push_back(child);
	}
	else
	{
		std::cout << "LOG:: Can't Perform GameObject::AddChild() as child is already attached" << std::endl;
	}
}

void kd::GameObject::RemoveChild(GameObject* child)
{
	auto it = std::find(m_Childs.begin(), m_Childs.end(), child);
	if (it != m_Childs.end())
	{
		child->m_Parent = nullptr;
		child->OnRemoved();
		m_Childs.erase(it);
	}
	else
	{
		std::cout << "LOG:: Can't Perform GameObject::RemoveChild() as child is not attached" << std::endl;
	}
}

void kd::GameObject::AddComponent(BaseComponent * pComponent)
{
	auto it = std::find(m_Components.begin(), m_Components.end(), pComponent);

	if (it == m_Components.end()) {
		pComponent->m_pGameObject = this;
		m_Components.push_back(pComponent);
	}
	else {
		std::cout << "LOG:: Can't Perform GameObject::AddComponent() as Component already existed" << std::endl;
	}
}

void kd::GameObject::RemoveComponent(kd::BaseComponent * pComponent)
{
	auto it = std::find(m_Components.begin(), m_Components.end(), pComponent);

	if (it != m_Components.end()) {
		m_Components.erase(it);
	}
	else {
		std::cout << "LOG:: Can't Perform GameObject::RemoveComponent() as Component already existed" << std::endl;
	}
}

void kd::GameObject::Initalize()
{
	for (BaseComponent* component : m_Components)
	{
		component->Initialize();
	}

	UpdateTransform();
}

void kd::GameObject::Update()
{
	UpdateTransform();

	for (BaseComponent* component : m_Components)
	{
		component->Update();
	}

	for(GameObject* child: m_Childs)
	{
		child->Update();
	}
}

void kd::GameObject::Render() const
{
	for (BaseComponent* component : m_Components)
	{
		component->Render();
	}

	for(GameObject* child: m_Childs)
	{
		child->Render();
	}
}

void kd::GameObject::OnRemoved()
{
	for (BaseComponent* component : m_Components)
	{
		component->OnGameObjectRemoved();
	}

	for(GameObject* child: m_Childs)
	{
		child->OnRemoved();
	}
}

void kd::GameObject::UpdateTransform()
{
	if(m_Parent)
	{
		//Apply the same flip as parent
		GetTransform().SetFlip(m_Parent->GetTransform().GetFlip());

		//Parent-Child Matrix Transformation
		glm::mat4 TParent = glm::translate(glm::mat4(1), m_Parent->GetTransform().GetPosition());
		glm::mat4 T = glm::translate(glm::mat4(1), GetTransform().GetLocalPosition());
		glm::mat4 S = glm::scale(glm::mat4(1), glm::vec3(GetTransform().GetLocalScale(),1));
		glm::mat4 SParent = glm::scale(glm::mat4(1), glm::vec3(m_Parent->GetTransform().GetScale(),1));
		glm::mat4 R = glm::rotate(glm::mat4(1),  glm::radians(GetTransform().GetLocalRotation()), glm::vec3(0,0,1));
		glm::mat4 RParent = glm::rotate(glm::mat4(1), glm::radians(m_Parent->GetTransform().GetRotation()), glm::vec3(0,0,1));

		glm::mat4 transform = TParent * RParent * SParent * T * R * S;
		m_Transform.SetPosition(transform[3].x, transform[3].y, transform[3].z);

		glm::vec4 rotation = glm::vec4(0, 0, m_Parent->GetTransform().GetRotation(), 1);
		glm::vec4 transformedRot = R * rotation;
		m_Transform.SetRotation(transformedRot.z);

		glm::vec4 scale = glm::vec4(m_Parent->GetTransform().GetScale(),1,1);
		glm::vec4 transformScale = S * scale; 
		m_Transform.SetScale(transformScale.x, transformScale.y);
	}
}

