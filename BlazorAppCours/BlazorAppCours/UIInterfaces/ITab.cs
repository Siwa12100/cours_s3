using Microsoft.AspNetCore.Components;

namespace BlazorAppCours.UIInterfaces
{
    public interface ITab
    {
        RenderFragment ChildContent { get; }
    }
}
